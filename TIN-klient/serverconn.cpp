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
}


void ServerConn::doSetup(QThread *cThread)
{

    connect(cThread,SIGNAL(started()),this, SLOT(odbierajWiadomosci()));

}

void ServerConn::odbierajWiadomosci()
{
        qDebug() << "server conn is online";

        char wiad[HEADER_SIZE];
        char *sup;

        read(gniazdo, wiad, HEADER_SIZE);

        Szyfrator szyfr;
        Naglowek nagl = szyfr.deszyfrujNaglowek(wiad, NULL);

        qDebug() << "----- got message typ == " << nagl.typ << " ---- ";
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
            break;

       case CZY_ISTNIEJE:
            emit czyIstnieje(id);
    }


    }
}
