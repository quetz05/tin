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
    wyjscie = false;

    //watek = new QThread();

    //this->moveToThread(watek);

    //connect(watek, SIGNAL(started()), this, SLOT(run()));

    //watek->start();
}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{
    if(sekret!=NULL) delete sekret;

    close(socket);// zamykamy gniazdo
}

void UserConnection::nowaWiadomosc(int id)
{


    //qDebug() << "nowa Wiadomosc SLOT!!";

    // pojawila sie nowa wiadomosc od rozmowy id losowy to wypychamy ja na gniazd
    //if(rozmowy[id]->czyWiadomosc(myid)){
    if(true) {
        QString wiadomosc = "";
        wiadomosc.append(rozmowy[id]->odbiezWiadomosc(myid));
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
///@todo
void UserConnection::zabij()
{
    this->wyslijPakiet(SERWER_NIEZYJE,myid,(QString*)NULL);
    this->wyjscie=true;// jeszcze cos
}


///Zrobione
void UserConnection::dodanyDoRozmowy(int idUsr, int idRozm,rozmowa *ro,bool czy)
{

    //qDebug() << "TUTAJ TUTAJ TUTAJ TUTAJ";

    if(idUsr==this->myid){


        rozmowy.insert(idRozm,ro);
        // czy cos jeszcze trzeba jeszcze powiadomic uzytkownika
        if(czy){// to my ja stworzylismy przed chwila
            qDebug() << "Se rozmowa sie stworzyla";
            wyslijPakiet(ROZPOCZNIJ_ROZMOWE,idRozm,(QString*)NULL);// wysylamy potwierdzenie ze stwozona rozmowa
            //return;
        }
        qDebug() << "Dodaj";
        wyslijPakiet(DODAJ_DO_ROZMOWY,idRozm,(QString*)NULL);
        connect(ro,SIGNAL(nowaWiadomosc(int)),this,SLOT(nowaWiadomosc(int)), Qt::DirectConnection);
    }
}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
///@todo
void UserConnection::run()
{
    unsigned int ilePrzeczytano = 0;
    unsigned int nowaPartia = 0;

    char naglowek[HEADER_SIZE + 1];
    char *content;
    char *temp;

    QString login;
    QString hash;
    QString wiadomosc;

    Szyfrator szyfr;
    Naglowek nagl;

    fd_set writefds;

    unsigned int filePackets = 0;

    while(!wyjscie){ // 0 kod wyjscia
        // tu obróbka danych i wyslanie nowych wiadomosci
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec= 100000;
        ilePrzeczytano = 0;
        nowaPartia = 0;
        temp = new char[HEADER_SIZE + 1];
        memset(temp, '\0', HEADER_SIZE + 1);
        memset(naglowek, '\0', HEADER_SIZE + 1);

        while (ilePrzeczytano < HEADER_SIZE) {

            FD_ZERO(&writefds);
            FD_SET(socket,&writefds);

            if(select(socket+1,&writefds,NULL,NULL,&tv)){
                //qDebug() << "attempting read, actual == " << ilePrzeczytano;
                nowaPartia = read(socket, temp, HEADER_SIZE - ilePrzeczytano);

            if (nowaPartia == 0) {
                wyjscie = true;
                break;
            }

                strncat(naglowek, temp, nowaPartia);
                ilePrzeczytano += nowaPartia;
            }else{
                if(wyjscie) break;
            }
        }

        if (wyjscie)
            break;

        nagl = szyfr.deszyfrujNaglowek(naglowek, NULL);

        delete [] temp;

        temp = new char[nagl.trueRozmiar + 1];
        content = new char[nagl.trueRozmiar + 1];
        memset(temp, '\0', nagl.trueRozmiar + 1);
        memset(content, '\0', nagl.trueRozmiar + 1);

        ilePrzeczytano = 0;
        nowaPartia = 0;

        while (ilePrzeczytano < nagl.trueRozmiar) {

            FD_ZERO(&writefds);
            FD_SET(socket,&writefds);

            if(select(socket+1,&writefds,NULL,NULL,&tv)){
                nowaPartia = read(socket, temp, nagl.trueRozmiar - ilePrzeczytano);
                strncat(content, temp, nowaPartia);
                ilePrzeczytano += nowaPartia;
            }else{
                if(wyjscie) break;
            }
        }

        char *plik;

        if  (nagl.typ != PLIK_TRANSFER)
            wiadomosc = szyfr.deszyfrujDane(content, sekret);
        else {
            qDebug() << "serwerDostal == " << content;
            plik = szyfr.deszyfrujPlik(content, sekret);
            qDebug() << "serwerOdkodowal == " << plik;
        }

        delete [] temp;
        delete [] content;

        switch (nagl.typ){

        case PLIK_POCZATEK : {

            qDebug() << "serwer -- plik_poczatek";
            filePackets = 0;
            wyslijPakiet(PLIK_POCZATEK, nagl.ID, &wiadomosc);

        } break;

        case PLIK_TRANSFER :{

            qDebug() << "serwer -- plik_transfer << " << ++filePackets;

            wyslijPakiet(PLIK_TRANSFER, nagl.ID, plik);

        } break;

        case PLIK_CHCE : {

            qDebug() << "serwer -- plik_chce";
            wyslijPakiet(PLIK_CHCE, nagl.ID, &wiadomosc);
        }break;

        case PLIK_KONIEC : {

            qDebug() << "serwer -- plik_koniec";
            wyslijPakiet(PLIK_KONIEC, nagl.ID, (QString*)NULL);

        } break;

            case ODLACZ_UZYTKOWNIKA : { // skladamy samokrytyke i odlaczamy sie z serwera
                qDebug() << "wyjscie --- ";
                wyjscie=true;
                // cos jeszcze musimy powiedziec serwerowi zeby nas usunol;
            } break;

            case REJESTRUJ : {
                login = wiadomosc.left(nagl.ID);
                hash = wiadomosc.right(wiadomosc.size()-nagl.ID);
                rejestruj(login,hash);
            } break;

            case WYSLIJ_WIADOMOSC:{ // zeby nie bylo wiadomosc przyszla do nas :)
                //qDebug() << "got == " << wiadomosc;
                if(rozmowy.contains(nagl.ID)) {
                    qDebug() << "this is the rozmowa you are looking for";
                    rozmowy[nagl.ID]->wyslijWiadomosc(wiadomosc);
                }
            } break;

            case LOGUJ_UZYTKOWNIKA:{
                login = wiadomosc.left(nagl.ID);
                hash = wiadomosc.right(wiadomosc.size()-nagl.ID);
                loguj(login,hash);
            } break;
  //          case SPRAWDZ_DOSTEPNOSC:// nie wiem czy to wogole bedziemy robic ale nie ch bedzie
  //              break;
            case ZAKONCZ_ROZMOWE:{
                // chcemy jeszcze rozlaczyc slota zanim zrobimy wszystko inne
                if(this->rozmowy.contains(nagl.ID)){
                    disconnect(rozmowy[nagl.ID],SIGNAL(nowaWiadomosc(int)),this,SLOT(nowaWiadomosc(int)));
                    // uzytkownik chce zakonczyc rozmowe
                    rozmowy.remove(nagl.ID);
                    emit opuszczamRozmowe(myid,nagl.ID);

                }
            } break;

            case ROZPOCZNIJ_ROZMOWE:{// tu bedzie trudniej bo rozpoczecie chociaz nie jest tak zle

                emit tworzeRozmowe(myid); // tu musimy pamietac aby potem rozruzniac zaproszenia
            // do naszych wlasnych rozmow
            } break;

            case DODAJ_DO_ROZMOWY:{

                int idRozm = wiadomosc.toInt();
                emit dodajeRozmowce(nagl.ID,idRozm);

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


}

// rejestracja zioma nasze pierwsze podejscie do bazy danych
void UserConnection::rejestruj(QString name, QString pass)
{
    BramaUzytkownikow  *brama = BramaUzytkownikow::getSharedInstance();
    if(brama->sprawdzUzytkownika(name)<=0){
        int id =brama->dodajUzytkownika(name,pass);
        // i wysylamy takie cos ze sie u
        wyslijPakiet(REJESTRUJ,id,(QString*)NULL);
    }
    else{
        //tu wysylamy wiadomosc ze juz taki ktos jest
        wyslijPakiet(REJESTRUJ,0,(QString*)NULL);
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
            wyslijPakiet(LOGUJ_UZYTKOWNIKA,id,(QString*)NULL);
            emit dodajeSieDoListy(myid,this);
            return;

        }
    }
    wyslijPakiet(LOGUJ_UZYTKOWNIKA,0,(QString*)NULL);
    // nie udalo sie zalogowac trzeba naszego goscia o tym powiadomic
}
// tu bedziemy wysylac nanana
void UserConnection::wyslijPakiet(char typ, unsigned int id, QString *dane)
{
    mutex.lock();

    Szyfrator szyfr;

    // tworzymy wiadomość
    QString dane1;
    if(dane == NULL){
        dane1 = "";
    } else {
        dane1 = *dane;
    }

    Wiadomosc wiad(typ, id, dane1, this->socket);
    unsigned int wielkosc;
    char *wiadomosc = szyfr.szyfruj(&wiad,sekret,&wielkosc);

    //qDebug() << "WYSYŁAM typ: " << typ;

    wiad.wyslijDoSerwera(wiadomosc, wielkosc);

    mutex.unlock();
}

void UserConnection::wyslijPakiet(char typ, unsigned int id, char *dane)
{
    mutex.lock();

    Szyfrator szyfr;

    // tworzymy wiadomość
    /*QString dane1;
    if(dane == NULL){
        dane1 = "";
    } else {
        dane1 = *dane;
    }*/

    Wiadomosc wiad(typ, id, QString(""), this->socket);
    unsigned int wielkosc;
    char *wiadomosc = szyfr.szyfrujPlik(&wiad,sekret,&wielkosc, dane, 256);

    qDebug() << "serwer wysyla pakiet == " << wiadomosc;

    //qDebug() << "WYSYŁAM typ: " << typ;

    wiad.wyslijDoSerwera(wiadomosc, wielkosc);

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
