#include "mainwindow.h"
#include <QApplication>

#include "Baza/bramaznajomych.h"
#include "ekranlogowania.h"
#include <QThread>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(znajomi_zasoby);
    QApplication a(argc, argv);

    ekranLogowania ek;
    ek.show();

    return a.exec();

}
