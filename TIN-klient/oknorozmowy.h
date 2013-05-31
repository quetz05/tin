#ifndef OKNOROZMOWY_H
#define OKNOROZMOWY_H

#include <QDialog>
#include <QString>
#include "../wiadomosc.h"


namespace Ui {
class oknoRozmowy;
}

class oknoRozmowy : public QDialog
{
    Q_OBJECT


private slots:

    void wpisywanieWiadomosci(const QString &);
    void wyslij();
    void zakoncz();

public:
    explicit oknoRozmowy(QWidget *parent = 0, QString login = "", QString rozmowca="", int socket=0);
    ~oknoRozmowy();



signals:
    void koniecRozmowy(const QString&);

    
private:
    Ui::oknoRozmowy *ui;
    QString wiadomosc;
    QString loginTwoj;
    QString loginRozmowcy;
    //ID rozmowy
    int ID;
    int gniazdo;
};

#endif // OKNOROZMOWY_H
