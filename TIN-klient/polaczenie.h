#ifndef POLACZENIE_H
#define POLACZENIE_H

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QDebug>


int gniazdo = 0;


bool polacz(const char* adres, int port)
{
    //adres serwera
    struct sockaddr_in serwer;
    struct hostent *hp;
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

    return true;
}





#endif // POLACZENIE_H
