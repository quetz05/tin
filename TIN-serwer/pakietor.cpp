#include "pakietor.h"

Pakietor::Pakietor(int soc,QObject *parent) :
    QObject(parent), conn(soc)
{
    socc = soc;
}

int Pakietor::odbiezPakiet(unsigned int *naglowek, unsigned int *id,
                           QString *wiadomosc,Klucz* kluczor)
{
    // tu bawimy sie szyfrowaniem
    Szyfrator szyfr;
    char* supp = new char[HEADER_SIZE+1];
    if(conn.odbiezPakiet(supp,HEADER_SIZE)<0) return -1;
    Naglowek nagl = szyfr.deszyfrujNaglowek(supp,kluczor);
    (*naglowek) = nagl.typ;
    (*id) = nagl.ID;
    delete [] supp;
    supp = new char[nagl.trueRozmiar + 1];
    if(conn.odbiezPakiet(supp,nagl.trueRozmiar)<0) return -1;
    if(wiadomosc!=NULL) (*wiadomosc) = szyfr.deszyfrujDane(supp,kluczor);
    delete [] supp;
    return wiadomosc->size();


}

int Pakietor::nadajPakiet(unsigned int naglowek, unsigned int id,
                          QString *wiadomosc,Klucz* kluczor)
{
    // tu bawimy sie szyfrowaniem
    mutek.lock();

    QString dane1;
    if(wiadomosc == NULL){
        dane1 = "";
    } else {
        dane1 = *wiadomosc;
    }

  //  Wiadomosc wiad(naglowek, id, dane1, this->socc);
  //  unsigned int wielkosc;
   // char *wiadomosc1 = szyfr.szyfruj(&wiad,kluczor,&wielkosc);
   // wiad.wyslijDoSerwera(wiadomosc1, wielkosc);

    Wyslij wiad(naglowek, id, dane1, this->socc, kluczor);
    wiad.wyslij();

    mutek.unlock();

}

void Pakietor::wyjdz()
{
    this->conn.wychodzimy();
}
