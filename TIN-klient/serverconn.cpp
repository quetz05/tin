#include "serverconn.h"
#include <unistd.h>
#include <netinet/in.h>
#include <QDebug>
#include "../wiadomosc.h"
#include "szyfrator.h"
#include <QApplication>

ServerConn::ServerConn(QObject *parent, int socket) : pakietor(socket),
    QObject(parent)
{
    gniazdo = socket;
    koniec = false;
}


void ServerConn::doSetup(QThread *cThread)
{

    connect(cThread,SIGNAL(started()),this, SLOT(odbierajWiadomosci()));
    connect(cThread,SIGNAL(finished()),this, SLOT(koncz()));
}

void ServerConn::odbierajWiadomosci()
{

    while(!koniec)// false - kod wyjscia
    {
        unsigned int naglowek;
        unsigned int id;
        QString wiadomosc;
        int dlugosc = pakietor.odbiezPakiet(&naglowek,&id,&wiadomosc,NULL);
        if(dlugosc<0)
            return;// wychodzimy w razie bledu :) lub zamkniecia

        //rozpoznanie typu wiadomosci
        switch(naglowek) {
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
            break;

        case SERWER_NIEZYJE:
            emit niezywySerwer();

        }

    }
}

void ServerConn::zakoncz()
{
    qDebug() << "Sie koniec sie dzieje";
    koniec = true;
}

void ServerConn::koncz()
{
    qDebug() << "KONIEC DEFINITYWNIE!!";
    emit koniecProgramu();
}
