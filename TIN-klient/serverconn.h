#ifndef SERVERCONN_H
#define SERVERCONN_H

#include <QThread>
//#include "polaczenie.h"


class ServerConn: public QObject
{
    Q_OBJECT

public:
    explicit ServerConn(QObject *parent = 0);
    void doSetup(QThread &cThread);

signals:

    void czyRejestracja(int ID);

public slots:

    void odbierajWiadomosci(int socket);

};

#endif // SERVERCONN_H
