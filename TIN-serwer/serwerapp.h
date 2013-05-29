#ifndef SERWERAPP_H
#define SERWERAPP_H

#include <QObject>
#include<QCoreApplication>
#include <QMap>
#include "userconnection.h"
class SerwerApp : public QObject
{
    Q_OBJECT
private:
    QCoreApplication *app;
    QMap<int,UserConnection> users;// mapa urzytkowników do przetrzymania
    int port;
public:
    explicit SerwerApp(QObject *parent = 0);

    void quit();
    

    void setPort(int value){port = value;}

signals:
    void finished();
public slots:
    //nasza funkcyja odpalajaca apke
    void run();

    //nasze powiadomienie ze ktos chce nas zamknac
    void AboutToQuitApp();
};

#endif // SERWERAPP_H
