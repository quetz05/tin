#ifndef WIADOMOSC_H
#define WIADOMOSC_H

#include <QString>

/// TYPY NAGLOWKOW
#define ODLACZ_UZYTKOWNIKA 1 //UWAGA!! uzywalne do konczenia petli obslugi
#define REJESTRUJ 2 // id dlogosc loginu dlugosc hasla= dlugosc - dlugosc loginu !!!!! login potem haslo
#define WYSLIJ_WIADOMOSC 3 // UWAGA!! tutaj pole id naglowku zawiera id rozmowy !!!!!
#define LOGUJ_UZYTKOWNIKA 4
#define SPRAWDZ_DOSTEPNOSC 5
#define ZAKONCZ_ROZMOWE 6
#define ROZPOCZNIJ_ROZMOWE 7 // id to id rozmowy brak danych
#define DODAJ_DO_ROZMOWY 8 // id to id uzytkownika rozmiar to id rozmowy
#define PLIK_TRANSFER 9
#define PLIK_CHETNI 10
#define PLIK_ODPYTAJ 11
#define UZYTKOWNIK_DOSTEPNY 12 //PRZESYLAMY INFORMACJE O DOSTEPNYM UZYTKOWNIKU ID TEGO UZYTKOWNIKA RZOMIAR 1 DOSTEPNY 0 NIEDOSTEPNY



class Naglowek
{
    public:
        char* typ;
        char* ID;
        char* rozmiar;
        int trueRozmiar;
};


class Wiadomosc
{


public:


    Wiadomosc(char typ, unsigned int ID, QString string, int gnia);
    ~Wiadomosc(){delete [] dane;}

    Naglowek naglowek;
    char *dane;
    bool wyslijDoSerwera();

    int gniazdo;

};






#endif // WIADOMOSC_H
