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

    unsigned int ileWyslano = 0;
    int nowaPartia = 0;
    fd_set writefds;
    while (ileWyslano < rozmiar) {

        FD_ZERO(&writefds);
        FD_SET(gniazdo,&writefds);

        if(select(gniazdo+1,NULL,&writefds,NULL,NULL)){
            nowaPartia = write(gniazdo, co, rozmiar- ileWyslano);
            if (nowaPartia != -1) {
                ileWyslano += nowaPartia;
                co += nowaPartia;
            }else{
                return false;
            }
        }
    }

    return true;
}
