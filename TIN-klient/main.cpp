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

    main.con->doSetup(&odbiorSerwer);
    main.con->moveToThread(&odbiorSerwer);

    odbiorSerwer.start();

    Szyfrator szyfr;

    //char *w = szyfr.szyfruj(QString("zażółć gęślą jaźń"), 1);
    //qDebug() << szyfr.deSzyfruj(w, 1);

    Wiadomosc wiad(WYSLIJ_WIADOMOSC, 12, QString("zażółć gęślą jaźń"), gniazdo);
    char *sz = szyfr.szyfruj(&wiad, 1);
    char *desz = new char[36];

    strncpy(desz, sz, 36);

    Naglowek nagl;

    nagl = szyfr.deszyfrujNaglowek(desz, 1);

    qDebug() << "rozmiar == " << nagl.trueRozmiar;

    char *dane = new char[nagl.trueRozmiar];

    for (int i = 36; i < 36 + nagl.trueRozmiar; ++i)
        dane[i - 36] = sz[i];

    qDebug() << "wywalka?";
    //strlen(dane);

    QString wynik = szyfr.deszyfrujDane(dane, 1).append('\0');

    qDebug() << "odebrano == " << wynik;

    //wiad.wyslijDoSerwera();

    //QString desz = szyfr.deSzyfruj(sz, 1);

    //qDebug() << desz;

  return a.exec();

}
