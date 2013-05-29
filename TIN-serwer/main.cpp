#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <iostream>
#include<cstdlib>
#include "serwerapp.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SerwerApp aplikacja;

    // moze tu sobie zrzucimy pewne wartości z argv zeby miec je jakby co i zeby nie przekazywac calosci do aplikacji
    //taka podstawowa obróbka
    int port;
    if(argc>1)
    {
        port = atoi(argv[1]);
    }//narazie port potraktujemy jako pierwszy paramettr wywołania
    else{
        std::cout<<"podaj port przy uruchamianiu\n";
        //return -1;
        port = 1111;
    }
    aplikacja.setPort(port);
    // podłączamy sygnały i sloty do obiektu qt bez ktorego nie dziala komunikacja miedzy watkami
    QObject::connect(&aplikacja,SIGNAL(finished()),&a,SLOT(quit()));
    QObject::connect(&a,SIGNAL(aboutToQuit()),&aplikacja,SLOT(AboutToQuitApp()));

    QTimer::singleShot(10,&aplikacja,SLOT(run()));

    return a.exec();
}
