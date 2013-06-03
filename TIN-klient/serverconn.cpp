#include "serverconn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <QDebug>
#include "../wiadomosc.h"
#include "szyfrator.h"

ServerConn::ServerConn(QObject *parent, int socket) :
    QObject(parent)
{
    gniazdo = socket;
    //watek = new QThread();

    //connect(watek, SIGNAL(started()), this, SLOT(odbierajWiadomosci()));

    //this->moveToThread(watek);
    //watek->start();
}


void ServerConn::doSetup(QThread *cThread)
{

    connect(cThread,SIGNAL(started()),this, SLOT(odbierajWiadomosci()));

}

void ServerConn::odbierajWiadomosci()
{
   /* qDebug() << "Dzialam se w tle";
    char wiad[4];

    //czytanie typu
    read(gniazdo,wiad,1);
    char typ = wiad[0];
    qDebug()<< QString("Naglowek: ") + QString(wiad[0])<<"\n";

    //czytanie ID
    read(gniazdo,wiad,4);
    unsigned int id = ntohs(*((unsigned int*)wiad));
   // qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";

    //czytanie dlugosci
    read(gniazdo,wiad,4);
    unsigned int rozmiar = *((unsigned int*)wiad);
    //qDebug()<< ntohs(*((unsigned int*)wiad))<<"\n";
*/

    while(1) {
    char wiad[HEADER_SIZE];
    char *sup;

    read(gniazdo, wiad, HEADER_SIZE);

    Szyfrator szyfr;
    Naglowek nagl = szyfr.deszyfrujNaglowek(wiad, NULL);

    qDebug() << "rozmiar == " << nagl.trueRozmiar;

    char typ = nagl.typ;
    unsigned int id = nagl.ID;
    unsigned int rozmiar = nagl.trueRozmiar;

    QString wiadomosc;


    sup = new char[rozmiar];

    memset(sup, '\0', rozmiar);

    read(gniazdo, sup, rozmiar);

    wiadomosc = szyfr.deszyfrujDane(sup, NULL);


    //rozpoznanie typu wiadomosci
    switch(typ)
    {
        case REJESTRUJ:

        emit czyRejestracja(id);
        break;

    case LOGUJ_UZYTKOWNIKA:

        emit czyZaloguj(id);
        break;

    case ROZPOCZNIJ_ROZMOWE:

        emit nowaRozmowa(id);
        break;

    case  DODAJ_DO_ROZMOWY:
        emit odbiorRozmowy(id);
        break;

   case WYSLIJ_WIADOMOSC:

        emit odebranaWiadomosc(id, wiadomosc);




    }
       /* case WYSLIJ_WIADOMOSC: // zeby nie bylo wiadomosc przyszla do nas :)

            for(unsigned int i=0;i<rozmiar;++i)
            {
                read(socket,wiad,2);
                wiadomosc.append(*((QChar*)wiad));
            }// nazbieralismy nasza wiadomosc

            //odbior wiadomosci -> wysłanie do okna

            break;
*/

}
}
