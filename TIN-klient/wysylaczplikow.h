#ifndef WYSYLACZPLIKOW_H
#define WYSYLACZPLIKOW_H

#include <QByteArray>
#include "../wiadomosc.h"
#include "szyfrator.h"
#include <QRunnable>
#include <QObject>
#include <QDataStream>
#include <QFile>

class WysylaczPlikow : public QObject, public QRunnable{

    Q_OBJECT

public:
    WysylaczPlikow(QFile *co, int socket, int doKogo, QObject *parent = 0);
    ~WysylaczPlikow();

public slots:
    void run();

private:
    int gniazdo;
    int idCelu;
    QFile *src;

};

#endif // WYSYLACZPLIKOW_H
