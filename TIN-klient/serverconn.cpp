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
    koniec = false;
}


void ServerConn::doSetup(QThread *cThread)
{

    connect(cThread,SIGNAL(started()),this, SLOT(odbierajWiadomosci()));

}

void ServerConn::odbierajWiadomosci()
{
    Szyfrator szyfr;
    Naglowek nagl;
    char naglowek[HEADER_SIZE + 1];
    char *content;
    char *temp;
    unsigned int ilePrzeczytano = 0;
    unsigned int nowaPartia = 0;
    QString wiadomosc;

    while(!koniec) {

        ilePrzeczytano = 0;
        nowaPartia = 0;

        temp = new char[HEADER_SIZE + 1];
        memset(temp, '\0', HEADER_SIZE + 1);
        memset(naglowek, '\0', HEADER_SIZE + 1);
        fd_set writefds;

        while (ilePrzeczytano < HEADER_SIZE) {


            FD_ZERO(&writefds);
            FD_SET(gniazdo,&writefds);


            if(select(gniazdo+1,&writefds,NULL,NULL,NULL))
            {
                nowaPartia = read(gniazdo, temp, HEADER_SIZE - ilePrzeczytano);
                strncat(naglowek, temp, nowaPartia);
                ilePrzeczytano += nowaPartia;
            }
        }

        nagl = szyfr.deszyfrujNaglowek(naglowek, NULL);

        ilePrzeczytano = 0;
        nowaPartia = 0;
        delete [] temp;

        temp = new char[nagl.trueRozmiar + 1];
        content = new char[nagl.trueRozmiar + 1];
        memset(temp, '\0', nagl.trueRozmiar + 1);
        memset(content, '\0', nagl.trueRozmiar + 1);

        if (ilePrzeczytano < nagl.trueRozmiar) {
            nowaPartia = read(gniazdo, temp, nagl.trueRozmiar - ilePrzeczytano);
            strncat(content, temp, nowaPartia);
            ilePrzeczytano += nowaPartia;
        }

        wiadomosc = szyfr.deszyfrujDane(content, NULL);

        delete [] temp;
        delete [] content;

        //rozpoznanie typu wiadomosci
        switch(nagl.typ) {
            case REJESTRUJ:
                emit czyRejestracja(nagl.ID);
            break;

            case LOGUJ_UZYTKOWNIKA:
                emit czyZaloguj(nagl.ID);
            break;

            case ROZPOCZNIJ_ROZMOWE:
                emit nowaRozmowa(nagl.ID);
            break;

            case  DODAJ_DO_ROZMOWY:
                emit odbiorRozmowy(nagl.ID);
            break;

            case WYSLIJ_WIADOMOSC:
                emit odebranaWiadomosc(nagl.ID, wiadomosc);
            break;

            case CZY_ISTNIEJE:
                emit czyIstnieje(nagl.ID);
            break;

        case SERWER_NIEZYJE:
            emit niezywySerwer();

        }

    }
}

void ServerConn::zakoncz()
{
    koniec = true;
}
