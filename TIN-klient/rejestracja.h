#ifndef REJESTRACJA_H
#define REJESTRACJA_H

#include <QDialog>
#include "info.h"
#include "../wiadomosc.h"

namespace Ui {
class Rejestracja;
}

class Rejestracja : public QDialog
{
    Q_OBJECT


private slots:
    //czytanie nicku
    void czytajNick(const QString &);
    //czytanie hasla
    void czytajHaslo(const QString &);
    //czytanie hasla 2
    void czytajHaslo2(const QString &);
    //rejestracja
    void rejestruj();
    void wyjscie();

signals:
    void zakoncz();
    
public:
    explicit Rejestracja(QWidget *parent = 0, int socket=0);
    ~Rejestracja();
    
private:
    Ui::Rejestracja *ui;
    QString login;
    QString haslo;
    QString haslo2;
    int gniazdo;

    info *oknoInformacji;
};

#endif // REJESTRACJA_H
