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

    if (write(gniazdo, co, rozmiar) == -1) {
        qDebug() << "nie bangla";
        return false;
    }

    return true;

}
