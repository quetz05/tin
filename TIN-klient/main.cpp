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

    unsigned int size;

    Wiadomosc wiad(WYSLIJ_WIADOMOSC, 12, QString("to jest jakiś bardzo długi tekst, który zaraz spróbuje przesłać sobie ja :)"), gniazdo);
    char *sz = szyfr.szyfruj(&wiad, 1, &size);

    qDebug() << "proba wyslania";

    wiad.wyslijDoSerwera(sz, size);


    //wiad.wyslijDoSerwera();

    //QString desz = szyfr.deSzyfruj(sz, 1);

    //qDebug() << desz;

  int i = a.exec();

  //Wiadomosc wiad(ODLACZ_UZYTKOWNIKA,0,"",gniazdo);
  //wiad.wyslijDoSerwera();

      return i;

}
