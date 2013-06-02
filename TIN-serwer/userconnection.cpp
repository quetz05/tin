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

UserConnection::UserConnection(QObject *parent) :
    QThread(parent)
{
    zalogowany = false;
    myid=-1;
}

UserConnection::UserConnection(int socket)
{
    myid=-1;
    this->socket = socket;
    zalogowany = false;
}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{


    close(socket);// zamykamy gniazdo
}

void UserConnection::nowaWiadomosc(int id)
{
    // pojawila sie nowa wiadomosc od rozmowy id losowy to wypychamy ja na gniazd
    if(rozmowy[id]->czyWiadomosc(myid)){
        QString wiadomosc = rozmowy[id]->odbiezWiadomosc(id);
        wyslijPakiet(WYSLIJ_WIADOMOSC,id,wiadomosc.size(),&wiadomosc);
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



    if(idUsr==this->myid){
        rozmowy.insert(idRozm,ro);
    }// czy cos jeszcze trzeba jeszcze powiadomic uzytkownika
    if(czy){// to my ja stworzylismy przed chwila
        qDebug() << "Se rozmowa sie stworzyla";
        wyslijPakiet(ROZPOCZNIJ_ROZMOWE,idRozm,0,NULL);// wysylamy potwierdzenie ze stwozona rozmowa
        return;
    }
    qDebug() << "Dodaj";
    wyslijPakiet(DODAJ_DO_ROZMOWY,idRozm,0,NULL);

}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
///@todo
void UserConnection::run()
{
    bool wyjscie=false;
    qDebug() << "wystartowal watek urzytkownika\n";
    while(!wyjscie){ // 0 kod wyjscia
     // tu obróbka danych i wyslanie nowych wiadomosci
        char wiad[4];

        read(socket,wiad,1);
        char typ = wiad[0];
        qDebug()<< wiad[0]<<"\n";
        read(socket,wiad,4);
        unsigned int id = ntohs(*((unsigned int*)wiad));
        qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";
        read(socket,wiad,4);
        unsigned int dlugosc =*((unsigned int*)wiad);
        qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";
        unsigned int rozmiar = ntohs(*((unsigned int*)wiad));
        qDebug() <<"Jestem blisko...";
        qDebug() <<typ;
        qDebug() <<"Jestem blisko...";
        QString login;
        QString hash;
        QString wiadomosc;
        switch(typ){
            case ODLACZ_UZYTKOWNIKA: // skladamy samokrytyke i odlaczamy sie z serwera
                wyjscie=true;
                break;
            case REJESTRUJ:

            qDebug() <<"Wszedłem w ciebie...";

                //tu odczytujemy login i haslo
                for(unsigned int i=0;i<id/2;++i){
                    read(socket,wiad,2);
                    login.append(*((QChar*)wiad));
                }

                for(unsigned int i=0;i<(rozmiar -id)/2;++i){
                    read(socket,wiad,2);
                    hash.append(*((QChar*)wiad));
                }
                rejestruj(login,hash);
                break;
            case WYSLIJ_WIADOMOSC: // zeby nie bylo wiadomosc przyszla do nas :)

                for(unsigned int i=0;i<((rozmiar/2));++i){
                    read(socket,wiad,2);
                    wiadomosc.append(*((QChar*)wiad));
                }// nazbieralismy nasza wiadomosc
                if(rozmowy.contains(id)) rozmowy[id]->wyslijWiadomosc(wiadomosc);
                break;
            case LOGUJ_UZYTKOWNIKA:
                // tu trzeba nam jakas funkcje do logowania

                //tu odczytujemy login i haslo
                for(unsigned int i=0;i<id/2;++i){
                    read(socket,wiad,2);
                    login.append(*((QChar*)wiad));
                }

                for(unsigned int i=0;i<(rozmiar -id)/2;++i){
                    read(socket,wiad,2);
                    hash.append(*((QChar*)wiad));
                }
                loguj(login,hash);
                break;
  //          case SPRAWDZ_DOSTEPNOSC:// nie wiem czy to wogole bedziemy robic ale nie ch bedzie
  //              break;
            case ZAKONCZ_ROZMOWE:
                // uzytkownik chce zakonczyc rozmowe
                emit opuszczamRozmowe(myid,id);
                break;
            case ROZPOCZNIJ_ROZMOWE:// tu bedzie trudniej bo rozpoczecie chociaz nie jest tak zle
                emit tworzeRozmowe(myid); // tu musimy pamietac aby potem rozruzniac zaproszenia
            // do naszych wlasnych rozmow
                break;
            case DODAJ_DO_ROZMOWY:
                emit dodajeRozmowce(id,rozmiar);
                break;
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
        /*for(int i=0;i<rozmiar;++i){
            read(socket,wiad,2);
            qDebug() << *((QChar*)wiad);
        }*/

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
        wyslijPakiet(REJESTRUJ,id,0,NULL);
    }
    else{
        //tu wysylamy wiadomosc ze juz taki ktos jest i kij mu w oko
        wyslijPakiet(REJESTRUJ,0,0,NULL);
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
            wyslijPakiet(LOGUJ_UZYTKOWNIKA,id,0,NULL);
            emit dodajeSieDoListy(myid,this);
            return;
        }
    }
    wyslijPakiet(LOGUJ_UZYTKOWNIKA,0,0,NULL);
    // nie udalo sie zalogowac trzeba naszego goscia o tym powiadomic
}
// tu bedziemy wysylac nanana
void UserConnection::wyslijPakiet(char typ, unsigned int id, unsigned int daneRozm, QString *dane)
{
    mutex.lock(); //i zabezpieczone panie jakby ktory tak chcial wejsc nie proszony

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
