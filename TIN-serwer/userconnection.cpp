#include "userconnection.h"
#include <unistd.h> // to jest wazny include z opcjami read i write
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include "../wiadomosc.h"
#include <QString>
#include "Baza/bramauzytkownikow.h"
#include "rozmowa.h"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>

UserConnection::UserConnection(QObject *parent)
{
    zalogowany = false;
    myid = -1;
    sekret = NULL;
}

UserConnection::UserConnection(int socket)
{
    myid = -1;
    this->socket = socket;
    zalogowany = false;
    sekret = NULL;

    watek = new QThread();

    this->moveToThread(watek);

    connect(watek, SIGNAL(started()), this, SLOT(run()));

    watek->start();
}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{
    if(sekret!=NULL) delete sekret;

    close(socket);// zamykamy gniazdo
}

void UserConnection::nowaWiadomosc(int id)
{

    qDebug() << "nowa Wiadomosc SLOT!!";

    // pojawila sie nowa wiadomosc od rozmowy id losowy to wypychamy ja na gniazd
    //if(rozmowy[id]->czyWiadomosc(myid)){
    if(true) {
        QString wiadomosc = "";
        wiadomosc.append(rozmowy[id]->odbiezWiadomosc(id));
        wyslijPakiet(WYSLIJ_WIADOMOSC,id,&wiadomosc);
    }
}

///@todo
void UserConnection::pojawilSieUsr(int idUsr, int status)
{
    if(!zalogowany && idUsr==myid){
        if(status){
            qDebug()<<"zalogowany urzytkownik\n";
            zalogowany = true;
        }
    }
}
///Zrobione
void UserConnection::dodanyDoRozmowy(int idUsr, int idRozm,rozmowa *ro,bool czy)
{

    qDebug() << "TUTAJ TUTAJ TUTAJ TUTAJ";

    if(idUsr==this->myid){
        rozmowy.insert(idRozm,ro);
        // czy cos jeszcze trzeba jeszcze powiadomic uzytkownika
        if(czy){// to my ja stworzylismy przed chwila
            qDebug() << "Se rozmowa sie stworzyla";
            wyslijPakiet(ROZPOCZNIJ_ROZMOWE,idRozm,NULL);// wysylamy potwierdzenie ze stwozona rozmowa
            return;
        }
        qDebug() << "Dodaj";
        wyslijPakiet(DODAJ_DO_ROZMOWY,idRozm,NULL);
        connect(ro,SIGNAL(nowaWiadomosc(int)),this,SLOT(nowaWiadomosc(int)), Qt::DirectConnection);
    }
}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
///@todo
void UserConnection::run()
{
    unsigned int ilePrzeczytano = 0;
    unsigned int nowaPartia = 0;
    bool wyjscie = false;
    char naglowek[HEADER_SIZE];
    char *content;
    char *temp;

    char *sup;

    char typ = 0;
    unsigned int id = 0;
    unsigned int rozmiar = 0;

    QString login;
    QString hash;
    QString wiadomosc;

    Szyfrator szyfr;
    Naglowek nagl;

    while(!wyjscie){ // 0 kod wyjscia
        // tu obróbka danych i wyslanie nowych wiadomosci

        ilePrzeczytano = 0;
        nowaPartia = 0;
        temp = new char[HEADER_SIZE];
        memset(temp, '\0', HEADER_SIZE);
        memset(naglowek, '\0', HEADER_SIZE);
        fd_set writefds;
        while (ilePrzeczytano < HEADER_SIZE) {

            FD_ZERO(&writefds);
            FD_SET(socket,&writefds);

            if(select(socket+1,&writefds,NULL,NULL,NULL)){
                qDebug() << "attempting read, actual == " << ilePrzeczytano;
                nowaPartia = read(socket, temp, HEADER_SIZE - ilePrzeczytano);
                strncat(naglowek, temp, nowaPartia);
                ilePrzeczytano += nowaPartia;
            }
        }

        qDebug() << "przeczytano lacznie == " << ilePrzeczytano;
        qDebug() << "naglowek == " << naglowek;

        //if (read(socket, wiad, HEADER_SIZE) == 0)
            //break;

        nagl = szyfr.deszyfrujNaglowek(naglowek, NULL);

        typ = nagl.typ;
        id = nagl.ID;
        rozmiar = nagl.trueRozmiar;

        delete [] temp;

        temp = new char[nagl.trueRozmiar];
        content = new char[nagl.trueRozmiar];
        memset(temp, '\0', nagl.trueRozmiar);
        memset(content, '\0', nagl.trueRozmiar);

        ilePrzeczytano = 0;
        nowaPartia = 0;

        qDebug() << "naglowek zaraportowal rozmiar == " << nagl.trueRozmiar;

        while (ilePrzeczytano < nagl.trueRozmiar) {

            FD_ZERO(&writefds);
            FD_SET(socket,&writefds);

            if(select(socket+1,&writefds,NULL,NULL,NULL)){
                nowaPartia = read(socket, temp, nagl.trueRozmiar - ilePrzeczytano);
                strncat(content, temp, nowaPartia);
                ilePrzeczytano += nowaPartia;
            }
        }

        qDebug() << "przeczytano Dane rozmiar == " << ilePrzeczytano;
        qDebug() << "dane == " << content;

        wiadomosc = szyfr.deszyfrujDane(content, sekret);

        delete [] temp;
        delete [] content;

        switch (nagl.typ){

            case ODLACZ_UZYTKOWNIKA : { // skladamy samokrytyke i odlaczamy sie z serwera
                qDebug() << "wyjscie --- ";
                wyjscie=true;
            } break;

            case REJESTRUJ : {
                login = wiadomosc.left(id);
                hash = wiadomosc.right(wiadomosc.size()-id);
                rejestruj(login,hash);
            } break;

            case WYSLIJ_WIADOMOSC:{ // zeby nie bylo wiadomosc przyszla do nas :)
                qDebug() << "got == " << wiadomosc;
                if(rozmowy.contains(id)) {
                    qDebug() << "this is the rozmowa you are looking for";
                    rozmowy[id]->wyslijWiadomosc(wiadomosc);
                }
            } break;

            case LOGUJ_UZYTKOWNIKA:{
                login = wiadomosc.left(id);
                hash = wiadomosc.right(wiadomosc.size()-id);
                loguj(login,hash);
            } break;
  //          case SPRAWDZ_DOSTEPNOSC:// nie wiem czy to wogole bedziemy robic ale nie ch bedzie
  //              break;
            case ZAKONCZ_ROZMOWE:{
                // uzytkownik chce zakonczyc rozmowe
                emit opuszczamRozmowe(myid,id);
            } break;

            case ROZPOCZNIJ_ROZMOWE:{// tu bedzie trudniej bo rozpoczecie chociaz nie jest tak zle

                emit tworzeRozmowe(myid); // tu musimy pamietac aby potem rozruzniac zaproszenia
            // do naszych wlasnych rozmow
            } break;

            case DODAJ_DO_ROZMOWY:{

                int idRozm = wiadomosc.toInt();
                emit dodajeRozmowce(id,idRozm);

            } break;

            case NAWIAZ_BEZPIECZNE:{
                Klucz nk = szyfr.stringDoKlucz(wiadomosc);
                sekret = new Klucz(nk);
            } break;
            /*case PLIK_TRANSFER:
                break;
            case PLIK_CHETNI:
                break;
            case PLIK_ODPYTAJ:
                break;
            case UZYTKOWNIK_DOSTEPNY:
                break;
*/
        }

    }
    sprzataj();
    emit finished(myid);

}

// rejestracja zioma nasze pierwsze podejscie do bazy danych
void UserConnection::rejestruj(QString name, QString pass)
{
    BramaUzytkownikow  *brama = BramaUzytkownikow::getSharedInstance();
    if(brama->sprawdzUzytkownika(name)<=0){
        int id =brama->dodajUzytkownika(name,pass);
        // i wysylamy takie cos ze sie u
        wyslijPakiet(REJESTRUJ,id,NULL);
    }
    else{
        //tu wysylamy wiadomosc ze juz taki ktos jest
        wyslijPakiet(REJESTRUJ,0,NULL);
    }
}

// logowanie uzytkownika
void UserConnection::loguj(QString name, QString pass)
{
    BramaUzytkownikow  *brama = BramaUzytkownikow::getSharedInstance();
    // najpierw sprawdzamy czy gosc istnieje
    int id = brama->sprawdzUzytkownika(name);
    // jak taki jest to sprawdzamy czy sie haslo zgadza
    if(id >0){
        QString haslo = brama->getHashPassword(id);
        if(!haslo.compare(pass)){
            qDebug() << "Hasło się zgadza!";
            myid=id;
            wyslijPakiet(LOGUJ_UZYTKOWNIKA,id,NULL);
            emit dodajeSieDoListy(myid,this);
            return;

        }
    }
    wyslijPakiet(LOGUJ_UZYTKOWNIKA,0,NULL);
    // nie udalo sie zalogowac trzeba naszego goscia o tym powiadomic
}
// tu bedziemy wysylac nanana
void UserConnection::wyslijPakiet(char typ, unsigned int id, QString *dane)
{
    mutex.lock();

    qDebug() << "---------- bede slal! typ == " << (int)typ << " ---------";

    Szyfrator szyfr;

    // tworzymy wiadomość
    QString dane1;
    if(dane==NULL){
        dane1 = "";
    }else{
        dane1 = *dane;
    }
    Wiadomosc wiad(typ,id,dane1,this->socket);
    unsigned int wielkosc;
    char *wiadomosc = szyfr.szyfruj(&wiad,sekret,&wielkosc);
     //i zabezpieczone panie jakby ktory tak chcial wejsc nie proszony
    // i wysylamy pod mutexem
    if(write(socket,wiadomosc,wielkosc)==-1){
        qDebug()<<"Błąd przy nadawaniu wiadomosci\n";
    }
    //delete wiadomosc;
    // to będzie z goła inaczej
    /*
    if(write(socket,&typ,1)==-1){
        qDebug()<<"Błąd przy nadawaniu typu nagłówka\n";
    }
    id = htons(id);
    char *usrid = (char*)(&id);
    if(write(socket,usrid,4)==-1){
        qDebug()<<"Błąd przy nadawaniu id\n";
    }
    daneRozm = htons(daneRozm);
    usrid = (char*)(&daneRozm);
    if(write(socket,&usrid,4)==-1){
        qDebug()<<"Błąd przy nadawaniu rozmiaru danych\n";
    }
    if(dane!=NULL){
        usrid = (char*)(dane->data());
        if(write(socket,&usrid,2*daneRozm)==-1){
            qDebug()<<"Błąd przy nadawaniu danych\n";
        }
    }
    */
    mutex.unlock();
}

// wywalamy sie
void UserConnection::sprzataj()
{
    // wywalamy sie ze wszystkich rozmow
    for(QMap<int,rozmowa*>::Iterator it=rozmowy.begin();it!=rozmowy.end();++it){
        emit opuszczamRozmowe(myid,it.key());
    }// tu nie musimy sie martwic o zazadzanie pamiecia rozmow bo to robi glowny watek serwera
}
