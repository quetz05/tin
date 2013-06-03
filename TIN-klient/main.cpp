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
    if(polacz((char*)"127.0.0.1",1111))
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

    Szyfrator szyfr;

    Klucz n = szyfr.wygenerujKlucz();
    QString s = szyfr.kluczDoStringa(&n);
    qDebug() << s;
    n = szyfr.stringDoKlucz(s);

    unsigned int size;
/*
    Wiadomosc wiad(WYSLIJ_WIADOMOSC, 12, QString("to jest jakiś bardzo długi tekst, który zaraz spróbuje przesłać sobie ja :)"), gniazdo);
    char *sz = szyfr.szyfruj(&wiad, NULL, &size);

    wiad.wyslijDoSerwera(sz, size);

    Wiadomosc wiad2(WYSLIJ_WIADOMOSC, 12, QString("zażółć gęślą jaźń"), gniazdo);
    char *sz2 = szyfr.szyfruj(&wiad2, NULL, &size);

    wiad.wyslijDoSerwera(sz2, size);

    Wiadomosc wiad3(WYSLIJ_WIADOMOSC, 12, QString(""), gniazdo);
    char *sz3 = szyfr.szyfruj(&wiad3, NULL, &size);

    wiad.wyslijDoSerwera(sz3, size);*/

    int i = a.exec();


  Wiadomosc wiad(ODLACZ_UZYTKOWNIKA,0,QString(""),gniazdo);
  unsigned int rozmiar;
  char *sz = szyfr.szyfruj(&wiad, NULL, &rozmiar);

  wiad.wyslijDoSerwera(sz, rozmiar);


      return i;

}
