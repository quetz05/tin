#include "mainwindow.h"
#include <QApplication>
#include "../wiadomosc.h"
#include "Baza/bramaznajomych.h"
#include "mainwindow.h"
#include <QThread>
#include "polaczenie.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    if(polacz((char*)"127.0.0.1",1112))
        qDebug() << "Połączony z serwerem...";
    else
        qDebug() << "Brak połączenia z serwerem...";

    Q_INIT_RESOURCE(znajomi_zasoby);
    Q_INIT_RESOURCE(images);

    qDebug() << qVersion();
    qDebug() << QT_VERSION_STR;

    QApplication a(argc, argv);

    QThread odbiorSerwer;

    MainWindow main(0,"",gniazdo);

    main.con->doSetup(&odbiorSerwer);
    main.con->moveToThread(&odbiorSerwer);

    odbiorSerwer.start();

    int i = a.exec();


    Wiadomosc wiad(ODLACZ_UZYTKOWNIKA,0,QString(""),gniazdo);
    unsigned int rozmiar;
    char *sz = szyfr.szyfruj(&wiad, NULL, &rozmiar);

    wiad.wyslijDoSerwera(sz, rozmiar);

    return i;

}
