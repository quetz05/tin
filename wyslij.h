#ifndef WYSLIJ_H
#define WYSLIJ_H

#include "szyfrator.h"

class Wyslij
{
public:
    Wyslij(char type, unsigned int id, QString string, int gnia, Klucz *key = NULL);
    ~Wyslij();

    void wyslij();


private:
    char typ;
    unsigned int ID;
    QString dane;
    int gniazdo;

    Wiadomosc *wiad;
    Szyfrator szyfr;
    Klucz *klucz;



};

#endif // WYSLIJ_H
