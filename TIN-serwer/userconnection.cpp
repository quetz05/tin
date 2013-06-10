#include "userconnection.h"
#include <unistd.h> // to jest wazny include z opcjami read i write
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "../wiadomosc.h"
#include <QString>
#include "Baza/bramauzytkownikow.h"
#include "rozmowa.h"
#include <sys/select.h>
#include <sys/time.h>
#include "polaczenie.h"



std::string naglowki[] = {
    "",
    "ODLACZ_UZYTKOWNIKA",
    "REJESTRUJ",
    "WYSLIJ_WIADOMOWSC",
    "LOGUJ_UZYTKOWNIKA",
    "SPRAWDZ_DOSTEPNOSC",
    "ZAKONCZ_ROZMOWE",
    "DODAJ_DO_ROZMOWY",
    "PLIK_TRANSFER",
    "PLIK_POCZATEK",
    "PLIK_KONIEC",
    "UZYTKOWNIK_DOSTEPNY",
    "NAWIAZ_BEZPIECZNE",
    "CZY_ISTNIEJE",
    "SERWER_NIEZYJE",
    "PLIK_NIECHCE",
    "PLIK_CHCE",
    "PLIK_TIMEOUT"
};

UserConnection::UserConnection(int socket) : pakieto(socket)
{
    myid = -1;
    this->gniazdo = socket;
    zalogowany = false;
    sekret = NULL;
    wyjscie = false;
    odbieraPlik = false;
    wysylajacy = NULL;

}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{
    if(sekret!=NULL) delete sekret;

    close(gniazdo);// zamykamy gniazdo
}

void UserConnection::nowaWiadomosc(int id)
{


    qDebug() << "nowa Wiadomosc SLOT!!";

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
    this->wyslijPakiet(SERWER_NIEZYJE,myid,NULL);
    this->wyjscie=true;// jeszcze cos
    this->pakieto.wyjdz();
}

void UserConnection::zacznijPrzesyl(bool *czy, UserConnection *ucon)
{
    if(!odbieraPlik){

        qDebug() << "tu ok";
        odbieraPlik=true;
        wysylajacy = ucon;
        *czy = true;

    }else{
        *czy = false;
    }

    qDebug() << "pomoc inside == " << (*czy);

}

void UserConnection::zakonczPrzesyl()
{
    odbieraPlik = false;
    this->wysylajacy = NULL;
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
            //return;
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
    Szyfrator szyfr;
    QString login;
    QString hash;
    unsigned int naglowek;
    unsigned int id;
    UserConnection* usrr;
    QString wiadomosc;
    bool czyIstnieje = false;


    while(!wyjscie){ // 0 kod wyjscia

        int dlogosc = pakieto.odbiezPakiet(&naglowek,&id,&wiadomosc,this->sekret);
        if(dlogosc<0) break;// wychodzimy w razie bledu :) lub zamkniecia

        qDebug() << "GOT MESSAGE == " << naglowki[naglowek - 1].c_str() << " :: od id == " << id;

        switch (naglowek){

            case PLIK_TIMEOUT : {
                if(this->wysylajacy){

                    wysylajacy->wyslijPakiet(PLIK_TIMEOUT, id, &wiadomosc);
                    wysylajacy=NULL;
                    odbieraPlik = false;
                }
            } break;
        
            case PLIK_NIECHCE : {
                if(this->wysylajacy){
                    wysylajacy->wyslijPakiet(PLIK_NIECHCE, id, &wiadomosc);
                }
            } break;
        
            case PLIK_POCZATEK : {
                emit giveUsr(&czyIstnieje,id,&usrr);
                bool pomoc=false;
                if(czyIstnieje){
                    usrr->zacznijPrzesyl(&pomoc,this);
                    if(pomoc)
                        usrr->wyslijPakiet(PLIK_POCZATEK, id, &wiadomosc);
                    else
                        wyslijPakiet(PLIK_NIECHCE, id, &wiadomosc);
                } else {
                    wyslijPakiet(PLIK_NIECHCE, id, &wiadomosc);
                }
            } break;
            case PLIK_KONIEC : {
                emit giveUsr(&czyIstnieje,id,&usrr);
                if(czyIstnieje){
                    usrr->zakonczPrzesyl();
                    usrr->wyslijPakiet(PLIK_KONIEC, id, &wiadomosc);
                }
            } break;
        
            case PLIK_TRANSFER: {
                emit giveUsr(&czyIstnieje,id,&usrr);
                if(czyIstnieje)
                    usrr->wyslijPakiet(PLIK_TRANSFER, id, &wiadomosc);
            } break;
            case PLIK_CHCE: {
                if(this->wysylajacy){
                    wysylajacy->wyslijPakiet(PLIK_CHCE, id, &wiadomosc);
                }
            } break;

            case ODLACZ_UZYTKOWNIKA : { // skladamy samokrytyke i odlaczamy sie z serwera
                qDebug() << "wyjscie --- ";
                wyjscie=true;
                // cos jeszcze musimy powiedziec serwerowi zeby nas usunol;
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
                // chcemy jeszcze rozlaczyc slota zanim zrobimy wszystko inne
                if(this->rozmowy.contains(id)){
                    disconnect(rozmowy[id],SIGNAL(nowaWiadomosc(int)),this,SLOT(nowaWiadomosc(int)));
                    // uzytkownik chce zakonczyc rozmowe
                    rozmowy.remove(id);
                    emit opuszczamRozmowe(myid,id);

                }
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

    Szyfrator szyfr;

    // tworzymy wiadomość
    QString dane1;
    if(dane == NULL){
        dane1 = "";
    } else {
        dane1 = *dane;
    }

    //Wiadomosc wiad(typ, id, dane1, this->gniazdo);
    //unsigned int wielkosc;
    //char *wiadomosc = szyfr.szyfruj(&wiad,sekret,&wielkosc);

    Wyslij wys(typ, id, dane1, this->gniazdo);
    wys.wyslij();

    qDebug() << "WYSYŁAM typ: " << naglowki[typ - 1].c_str() << " == " << (int) typ << " :: do == " << id;

    //wiad.wyslijDoSerwera(wiadomosc, wielkosc);

    mutex.unlock();
}

// wywalamy sie
void UserConnection::sprzataj()
{
    if(this->wysylajacy)    wysylajacy->wyslijPakiet(PLIK_TIMEOUT, this->myid, NULL);
    // wywalamy sie ze wszystkich rozmow
    for(QMap<int,rozmowa*>::Iterator it=rozmowy.begin();it!=rozmowy.end();++it){
        emit opuszczamRozmowe(myid,it.key());
    }// tu nie musimy sie martwic o zazadzanie pamiecia rozmow bo to robi glowny watek serwera
}

