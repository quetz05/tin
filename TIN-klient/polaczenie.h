#ifndef POLACZENIE_H
#define POLACZENIE_H


static const int TYP_PLIK_ODPYTAJ = 1; // odpytaj użytkownik czy chcą odebrać plik
static const int TYP_PLIK_CHETNI = 2; // poinformuj nadawcę, ilu jest chętnych
static const int TYP_PLIK_TRANSFER = 3;// pakiet z plikiem
static const int TYP_REJESTRUJ = 4; // rejestracja nowego użytkownika
static const int TYP_LOGUJ = 5; //

typedef struct Naglowek
{
    int typ;
    int ID;
    int rozmiar;


}Naglowek;


typedef struct Wiadomosc
{
   Naglowek naglowek;
   char dane[500];

}Wiadomosc;


#endif // POLACZENIE_H
