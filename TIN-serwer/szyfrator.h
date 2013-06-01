#ifndef SZYFRATOR_H
#define SZYFRATOR_H

#include <QString>

class Szyfrator
{
public:
    Szyfrator();

    char* szyfruj(QString dane, int klucz);
    QString deSzyfruj(const char* dane, int klucz);
};

#endif // SZYFRATOR_H
