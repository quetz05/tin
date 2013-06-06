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
    explicit oknoRozmowy(QWidget *parent = 0, int id = 0, int socket=0, QString login = "");
    ~oknoRozmowy();
    void wyswietlWiadomosc(QString wiadomosc);

    void keyPressEvent( QKeyEvent *keyevent );

signals:
    void koniecRozmowy(const int);

    
private:
    Ui::oknoRozmowy *ui;
    QString wiadomosc;
    QString uzytkownik;

    //ID rozmowy
    int ID;
    int gniazdo;
    Wiadomosc *wiad;
    QList <QString> rozmowcy;
};

#endif // OKNOROZMOWY_H
