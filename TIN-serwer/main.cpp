#include "mainwindow.h"
#include <QApplication>

#include "Baza/bramauzytkownikow.h"
#include <qdebug.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    BramaUzytkownikow test;
    qDebug() << test.sprawdzUzytkownika(1);
    return a.exec();
}
