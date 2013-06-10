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
        connect(cThread,SIGNAL(destroyed()),this, SLOT(koncz()));
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
        {
            qDebug() <<"Czy cygan dostał gruz?";
            emit thread()->terminate();
            return;// wychodzimy w razie bledu :) lub zamkniecia
        }
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

        case PLIK_POCZATEK:
            emit plikObiorStart(id, wiadomosc);
            break;

        case PLIK_TRANSFER:
            emit plikOdbiorTransfer(wiadomosc, id);
            break;

        case PLIK_CHCE:
            emit plikWysylStart();
            break;

        case PLIK_KONIEC:
            emit plikOdbiorKoniec();
            break;

        case PLIK_NIECHCE:
            emit plikNiechce();
            break;

        case PLIK_TIMEOUT:
            emit plikTimeout();

        case SERWER_NIEZYJE:
            emit niezywySerwer();
            break;


        }

    }

}

void ServerConn::zakoncz()
{
    qDebug() << "Sie koniec sie dzieje";
    koniec = true;
    pakietor.wyjdz();
}

void ServerConn::koncz()
{
    qDebug() << "KONIEC DEFINITYWNIE!!";
    emit koniecProgramu();
}
