#ifndef WIADOMOSC_H
#define WIADOMOSC_H

/// TYPY NAGLOWKOW
#define ODLACZ_UZYTKOWNIKA 1 //UWAGA!! uzywalne do konczenia petli obslugi
#define REJESTRUJ 2
#define WYSLIJ_WIADOMOSC 3 // UWAGA!! tutaj pole id naglowku zawiera id rozmowy !!!!!
#define LOGUJ_UZYTKOWNIKA 4
#define SPRAWDZ_DOSTEPNOSC 5
#define ZAKONCZ_ROZMOWE 6
#define ROZPOCZNIJ_ROZMOWE 7
#define DODAJ_DO_ROZMOWY 8
#define PLIK_TRANSFER 9
#define PLIK_CHETNI 10
#define PLIK_ODPYTAJ 11
#define UZYTKOWNIK_DOSTEPNY 12 //PRZESYLAMY INFORMACJE O DOSTEPNYM UZYTKOWNIKU ID TEGO UZYTKOWNIKA RZOMIAR 1 DOSTEPNY 0 NIEDOSTEPNY



class Naglowek
{
    public:
        char typ;
        int ID;
        int rozmiar;
};


class Wiadomosc
{


public:


    Wiadomosc() {ilosc = 1024;dane=new char[ilosc];}

    Wiadomosc(int x) {ilosc = x;dane=new char[ilosc];}
    ~Wiadomosc(){delete [] dane;}
    Naglowek naglowek;

    private:
        int ilosc;
        char *dane;

};

#endif // WIADOMOSC_H
