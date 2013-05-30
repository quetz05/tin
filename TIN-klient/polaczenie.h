#ifndef POLACZENIE_H
#define POLACZENIE_H

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define TYP_PLIK_ODPYTAJ 1; // odpytaj użytkownik czy chcą odebrać plik
#define TYP_PLIK_CHETNI 2; // poinformuj nadawcę, ilu jest chętnych
#define TYP_PLIK_TRANSFER 3;// pakiet z plikiem
#define TYP_REJESTRUJ 4; // rejestracja nowego użytkownika
#define TYP_LOGUJ 5; // logowanie

int gniazdo = 0;


bool polacz(char* adres, int port)
{
    //adres serwera (port 1111)
    struct sockaddr_in serwer;
    struct hostent *hp;
    //char bufor[1024];

    //inet_aton(adres,address);
    struct in_addr ipv4addr;
    inet_pton(AF_INET, adres, &ipv4addr);

    /* Create socket. */
    gniazdo = socket(AF_INET, SOCK_STREAM, 0 );

    if (gniazdo == -1)
    {
        qDebug() << "Błąd przy utworzeniu gniazda";
        return false;
    }

    /* uzyskajmy adres IP z nazwy ... */
    serwer.sin_family = AF_INET;

    hp = gethostbyaddr(&ipv4addr, 4,AF_INET);

    /* hostbyname zwraca strukture zawierajaca adres danego hosta */
    if (hp == (struct hostent *) 0)
    {
        qDebug() << "Nieznany adres: "<< adres;
        return false;
    }

    memcpy((char *) &serwer.sin_addr, (char *) hp->h_addr, hp->h_length);

    serwer.sin_port = htons(port);

    if (connect(gniazdo, (struct sockaddr *) &serwer, sizeof serwer) == -1)
    {
        qDebug() << "Blad przy polaczeniu...";
        return false;
    }

   /* if (write( gniazdo, DATA, sizeof DATA ) == -1)
    {
        qDebug() << "Błąd przy wysylaniu wiadomosci...";
        return false;
    }*/

    return true;
}





#endif // POLACZENIE_H
