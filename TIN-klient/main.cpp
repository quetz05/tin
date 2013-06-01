#include "mainwindow.h"
#include <QApplication>
#include "../wiadomosc.h"
#include "Baza/bramaznajomych.h"
#include "ekranlogowania.h"
#include <QThread>
#include "polaczenie.h"
#include <QDebug>
#include "szyfrator.h"


int main(int argc, char *argv[])
{
    if(polacz((char*)"127.0.0.1",1111))
        qDebug() << "Połączony z serwerem...";
    else
        qDebug() << "Brak połączenia z serwerem...";

    Wiadomosc trolo(3,13,QString("Rududa Bartku? Czy nie rududa? Oto jest pytanie! ąęćśżź"),gniazdo);

    trolo.wyslijDoSerwera();


    Q_INIT_RESOURCE(znajomi_zasoby);
    QApplication a(argc, argv);

    //ekranLogowania ek;
    //ek.show();

    Szyfrator szyfr;
    char *sz = szyfr.szyfruj(QString("zażółć gęślą jaźń"), 1);

    qDebug() << sz;

    QString desz = szyfr.deSzyfruj(sz, 1);

    qDebug() << desz;

    return a.exec();

}
