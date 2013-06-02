#ifndef SZYFRATOR_H
#define SZYFRATOR_H

#include <QString>
#include "../wiadomosc.h"

#define HEADER_SIZE 36

class Szyfrator
{
public:
    Szyfrator();

    char* szyfruj(Wiadomosc *wiad, int klucz, unsigned int *pSize);

    Naglowek deszyfrujNaglowek(char *data, int klucz);
    QString deszyfrujDane(char* data, int klucz);

    char* szyfruj(QString dane, int klucz);
    QString deSzyfruj(char* dane, int klucz);
};

#endif // SZYFRATOR_H
