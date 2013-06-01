#ifndef SERVERCONN_H
#define SERVERCONN_H

#include <QThread>
//#include "polaczenie.h"


class ServerConn: public QObject
{
    Q_OBJECT

public:
    explicit ServerConn(QObject *parent = 0, int socket = 0);
    void doSetup(QThread &cThread);

signals:

    void czyRejestracja(int ID);
    void zaloguj();

public slots:

    void odbierajWiadomosci();

private:
    int gniazdo;

};

#endif // SERVERCONN_H
