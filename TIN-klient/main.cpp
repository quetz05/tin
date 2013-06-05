#include "mainwindow.h"
#include <QApplication>
#include "../wiadomosc.h"
#include "Baza/bramaznajomych.h"
#include "mainwindow.h"
#include <QThread>
#include "polaczenie.h"
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <QDebug>
#include <string>
#include <QMessageBox>


int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(znajomi_zasoby);
    Q_INIT_RESOURCE(images);

    qDebug() << qVersion();
    qDebug() << QT_VERSION_STR;

    QApplication a(argc, argv);

    bool jestPlik = false;
    int port;
    std::string temp;
    const char * ip;

     FILE *fp;
     char c[80];
     QString plik;
     if ( (fp=fopen("../ip", "ro")) != NULL )
     {
        while( fgets( c, 80, fp ) != NULL )
            plik.append(c);
        fclose(fp);
        jestPlik = true;
     }
     else
     {
         QMessageBox wiad;
         wiad.setWindowTitle("Błąd otwarcia pliku");
         wiad.setText("Nie ma pliku, nie ma serwera!");
         wiad.addButton(QMessageBox::Ok);
         wiad.setIcon(QMessageBox::Warning);
         wiad.exec();

         return 0;
     }

     if(jestPlik)
     {
         temp= plik.section("|",1,1).toStdString();
         port = plik.section("*",1,1).toInt();
         ip = temp.c_str();
     }


    if(polacz(ip,port))
        qDebug() << "Połączony z serwerem...";
    else
    {
        QMessageBox wiadomosc;
        wiadomosc.setWindowTitle("Brak połączenia z serwerem.");
        wiadomosc.setText("WYRAŹNIE informuję użytkownika, że nie może się połączyć z serwerem!");
        wiadomosc.addButton(QMessageBox::Ok);
        wiadomosc.setIcon(QMessageBox::Warning);
        wiadomosc.exec();

        return 0;

    }



    QThread odbiorSerwer;

    MainWindow main(0,"",gniazdo);

    main.con->doSetup(&odbiorSerwer);
    main.con->moveToThread(&odbiorSerwer);

    odbiorSerwer.start();

    int i = a.exec();

    Szyfrator szyfr;
    Wiadomosc wiad(ODLACZ_UZYTKOWNIKA,0,QString(""),gniazdo);
    unsigned int rozmiar;
    char *sz = szyfr.szyfruj(&wiad, NULL, &rozmiar);

    wiad.wyslijDoSerwera(sz, rozmiar);

    return i;

}
