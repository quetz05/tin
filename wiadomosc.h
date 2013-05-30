#ifndef WIADOMOSC_H
#define WIADOMOSC_H

class Naglowek
{
    public:
        int typ;
        int ID;
        int rozmiar;
};


class Wiadomosc
{

    public:

        Wiadomosc() {ilosc = 1024;}
        Wiadomosc(int x) {ilosc = x;}
        Naglowek naglowek;

    private:
        int ilosc;
        char dane[ilosc];

};

#endif // WIADOMOSC_H
