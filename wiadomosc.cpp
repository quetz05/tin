#include "wiadomosc.h"
#include <QDebug>
#include <unistd.h>
#include <arpa/inet.h>
#include <QChar>

Wiadomosc::Wiadomosc(char typ, unsigned int ID, QString string, int gnia)
{
    naglowek.typ = new char;
    *(naglowek.typ) = typ;

    trueDane = string;



    unsigned int *wsk = new unsigned int(htons(ID));
    naglowek.ID = (char*)wsk;
    naglowek.trueRozmiar = 2*trueDane.length();

    wsk = new unsigned int(htons(naglowek.trueRozmiar));
    naglowek.rozmiar = (char*)wsk;
    gniazdo = gnia;

    QChar *tempDane = trueDane.data();


    dane = (char*) tempDane;


}


bool Wiadomosc::wyslijDoSerwera()
{

     if (write(gniazdo, this->naglowek.typ, 1) == -1)
     {
         qDebug() << "Błąd przy wysylaniu naglowka wiadomosci...";
         return false;
     }

     if (write(gniazdo, this->naglowek.ID, 4) == -1)
     {
         qDebug() << "Błąd przy wysylaniu ID wiadomosci...";
         return false;
     }

     if (write(gniazdo, this->naglowek.rozmiar, 4) == -1)
     {
         qDebug() << "Błąd przy wysylaniu rozmiaru wiadomosci...";
         return false;
     }

     if (write(gniazdo, this->dane, this->naglowek.trueRozmiar) == -1)
     {
         qDebug() << "Błąd przy wysylaniu danych wiadomosci...";
         return false;
     }

     return true;
}
