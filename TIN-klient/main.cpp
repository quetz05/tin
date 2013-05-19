#include "mainwindow.h"
#include <QApplication>

#include "Baza/bramaznajomych.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(znajomi_zasoby);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();


}
