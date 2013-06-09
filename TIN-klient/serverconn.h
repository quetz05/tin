#ifndef SERVERCONN_H
#define SERVERCONN_H

#include <QThread>
#include <sys/select.h>
#include "../pakietor.h"


class ServerConn: public QObject
{
    Q_OBJECT

/**
 * @brief The ServerConn class
 * Dzialajaca w odrebnym watku odpowiada za odbieranie wiadomosci z serwera i kierowanie
 * ich do odpowiednich klas
*
*/
public:
    explicit ServerConn(QObject *parent = 0, int socket = 0);
    void doSetup(QThread *cThread);

signals:

    void czyRejestracja(int);
    void czyZaloguj(int);
    //sygnał, że tworzona jest nowa rozmowa
    void nowaRozmowa(int);
    //sygnał, że ktoś chce z nami rozmawiać
    void odbiorRozmowy(int);
    //sygnał z odpowiedzią na istnienie nowego znajomego
    void czyIstnieje(const int);
    //sygnał odebrania nowej wiadomosci
    void odebranaWiadomosc(int,QString);
    //serwer padl
    void niezywySerwer();
    //sygnal zakonczenia programu
    void koniecProgramu();


public slots:
    void zakoncz();
    void odbierajWiadomosci();
    void koncz();


private:
    int gniazdo;
    QThread *watek;
    bool koniec;
    Pakietor pakietor;
};

#endif // SERVERCONN_H
