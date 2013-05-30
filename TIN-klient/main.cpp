#include "mainwindow.h"
#include <QApplication>

#include "Baza/bramaznajomych.h"
#include "ekranlogowania.h"
#include <QThread>
#include "polaczenie.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    if(polacz((char*)"192.168.0.12",1111))
        qDebug() << "Połączony z serwerem...";
    else
        qDebug() << "Brak połączenia z serwerem...";


    Q_INIT_RESOURCE(znajomi_zasoby);
    QApplication a(argc, argv);

    ekranLogowania ek;
    ek.show();

    return a.exec();

}
