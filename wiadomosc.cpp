#include "wiadomosc.h"
#include <QDebug>
#include <unistd.h>
#include <arpa/inet.h>
#include <QChar>

Wiadomosc::Wiadomosc(char typ, unsigned int ID, QString string, int gnia)
{
    naglowek.typ = typ;
    naglowek.ID = htons(ID);
    trueDane = string;
    gniazdo = gnia;
}


bool Wiadomosc::wyslijDoSerwera(const char *co, unsigned int rozmiar)
{

    qDebug() << "sending WIADOMOSC == " << co;

    unsigned int ileWyslano = 0;
    unsigned int nowaPartia = 0;
    fd_set writefds;
    while (ileWyslano < rozmiar) {

        FD_ZERO(&writefds);
        FD_SET(socket,&writefds);

        if(select(socket+1,NULL,&writefds,NULL,NULL)){
            nowaPartia = write(gniazdo, co, rozmiar- ileWyslano);
            if (nowaPartia != -1) {
                ileWyslano += nowaPartia;
                co += nowaPartia;
            }
        }
    }

    return true;
}
