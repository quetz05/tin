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
    Szyfrator szyfr;
    Naglowek nagl;
    char naglowek[HEADER_SIZE + 1];
    char *content;
    char *temp;
    unsigned int ilePrzeczytano = 0;
    unsigned int nowaPartia = 0;

    QString wiadomosc;

    while(1) {

        ilePrzeczytano = 0;
        nowaPartia = 0;

        temp = new char[HEADER_SIZE + 1];
        memset(temp, '\0', HEADER_SIZE + 1);
        memset(naglowek, '\0', HEADER_SIZE + 1);

        while (ilePrzeczytano < HEADER_SIZE) {
            nowaPartia = read(gniazdo, temp, HEADER_SIZE - ilePrzeczytano);
            strncat(naglowek, temp, nowaPartia);
            ilePrzeczytano += nowaPartia;
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
        }

    }
}
