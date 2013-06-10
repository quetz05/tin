#ifndef WYSYLACZPLIKOW_H
#define WYSYLACZPLIKOW_H

#include <QByteArray>
#include "../wiadomosc.h"
#include "szyfrator.h"
#include <QRunnable>
#include <QObject>
#include <QDataStream>
#include <QFile>
#include <QMutex>

class WysylaczPlikow : public QObject, public QRunnable{

    Q_OBJECT

public:
    WysylaczPlikow(QFile *co, int socket, int doKogo, QObject *parent = 0);
    ~WysylaczPlikow();

    void timeout();

public slots:
    void run();

signals:
    void koniec();

private:
    QMutex mutex;
    int gniazdo;
    int idCelu;
    bool anuluj;
    QFile *src;

};

#endif // WYSYLACZPLIKOW_H
