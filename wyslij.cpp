#include "wyslij.h"

Wyslij::Wyslij(char type, unsigned int id, QString string, int gnia, Klucz *key)
{
    typ = type;
    ID = id;
    dane = string;
    gniazdo = gnia;
    klucz = key;

    wiad = new Wiadomosc(typ, ID, dane, gniazdo);

}

void Wyslij::wyslij()
{
    unsigned int size;
    char *sz = szyfr.szyfruj(wiad, klucz, &size);
    wiad->wyslijDoSerwera(sz, size);
}

Wyslij::~Wyslij()
{

    if(wiad)
    {
        delete wiad;
        wiad = NULL;
    }
    if (klucz)
    {
        delete klucz;
        klucz = NULL;
    }
}
