#include "mainwindow.h"
#include <QApplication>
#include "../wiadomosc.h"
#include "Baza/bramaznajomych.h"
#include "mainwindow.h"
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



    Q_INIT_RESOURCE(znajomi_zasoby);
    QApplication a(argc, argv);

    QThread odbiorSerwer;


    MainWindow main(0,"",gniazdo);

    main.con->doSetup(odbiorSerwer);
    main.con->moveToThread(&odbiorSerwer);

    odbiorSerwer.start();


  /*  Szyfrator szyfr;
    char *sz = szyfr.szyfruj(QString("zażółć gęślą jaźń"), 1);

    qDebug() << sz;

    QString desz = szyfr.deSzyfruj(sz, 1);

    qDebug() << desz;*/

  return a.exec();

}
