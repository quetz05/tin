#include "wyslij.h"

Wyslij::Wyslij(char type, unsigned int id, QString string, int gnia)
{
    typ = type;
    ID = id;
    dane = string;
    gniazdo = gnia;

    wiad = new Wiadomosc(typ, ID, dane, gniazdo);

    this->wyslij();

}

void Wyslij::wyslij()
{
    unsigned int size;
    char *sz = szyfr.szyfruj(wiad, NULL, &size);
    wiad->wyslijDoSerwera(sz, size);
}
