#ifndef WYSLIJ_H
#define WYSLIJ_H

#include "szyfrator.h"

class Wyslij
{
public:
    Wyslij(char type, unsigned int id, QString string, int gnia);


private:
    void wyslij();

    char typ;
    unsigned int ID;
    QString dane;
    int gniazdo;

    Wiadomosc *wiad;
    Szyfrator szyfr;



};

#endif // WYSLIJ_H
