#include "serverconn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <QDebug>
#include "../wiadomosc.h"


ServerConn::ServerConn(QObject *parent, int socket) :
    QObject(parent)
{
    gniazdo = socket;

}


void ServerConn::doSetup(QThread &cThread)
{

    connect(&cThread,SIGNAL(started()),this, SLOT(odbierajWiadomosci()));

}

void ServerConn::odbierajWiadomosci()
{

   char wiad[4];

    //czytanie typu
    read(gniazdo,wiad,1);
    char typ = wiad[0];
    qDebug()<< QString(wiad[0])<<"\n";

    //czytanie ID
    read(gniazdo,wiad,4);
    unsigned int id = ntohs(*((unsigned int*)wiad));
    qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";

    //czytanie dlugosci
    read(gniazdo,wiad,4);
    unsigned int rozmiar = *((unsigned int*)wiad);
    qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";

    QString wiadomosc;



    //rozpoznanie typu wiadomosci
    switch(typ)
    {
        case REJESTRUJ:

            //tu odczytujemy przydzielone ID
            //id to jest ID, reszta nas nie ineteresuje
        emit czyRejestracja(id);

        break;
    }
       /* case WYSLIJ_WIADOMOSC: // zeby nie bylo wiadomosc przyszla do nas :)

            for(unsigned int i=0;i<rozmiar;++i)
            {
                read(socket,wiad,2);
                wiadomosc.append(*((QChar*)wiad));
            }// nazbieralismy nasza wiadomosc

            //odbior wiadomosci -> wysłanie do okna

            break;

        case LOGUJ_UZYTKOWNIKA:
            // tu trzeba nam jakas funkcje do logowania

            //tu odczytujemy login i haslo
            for(unsigned int i=0;i<id;++i)
            {
                read(socket,wiad,2);
                login.append(*((QChar*)wiad));
            }

            for(unsigned int i=0;i<rozmiar -id;++i)
            {
                read(socket,wiad,2);
                hash.append(*((QChar*)wiad));
            }
            loguj(login,hash);
            break;


        case ROZPOCZNIJ_ROZMOWE:// tu bedzie trudniej bo rozpoczecie chociaz nie jest tak zle
            emit tworzeRozmowe(myid); // tu musimy pamietac aby potem rozruzniac zaproszenia
        // do naszych wlasnych rozmow
            break;

    }*/



}
