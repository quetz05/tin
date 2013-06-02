#ifndef EKRANLOGOWANIA_H
#define EKRANLOGOWANIA_H

#include <QDialog>
#include <QString>
#include "info.h"
#include "rejestracja.h"

namespace Ui {
class ekranLogowania;
}

class ekranLogowania : public QDialog
{
    Q_OBJECT


private slots:

    void czytajLogin(QString);
    void czytajHaslo(QString);
    void zakoncz();
    void zaloguj();
    void rejestruj();
    void zakonczRejestracje();



public slots:
    void rejCzyRejestracja(int id) {emit SIGczyRejestracja(id);}
    void sprawdzZaloguj(int);
    void koniecInfo() {delete oknoInformacji; oknoInformacji = NULL;}



signals:
    void logowanie(const QString&);
    void SIGczyRejestracja(int);
    
public:
    explicit ekranLogowania(QWidget *parent = 0, int socket=0);
    ~ekranLogowania();
    QString pobierzLogin();
    bool dostep;
    
private:
    QString login;
    QString haslo;

    Wiadomosc *wiad;

    Rejestracja *rej;
    info *oknoInformacji;
    int gniazdo;
    Ui::ekranLogowania *ui;
};

#endif // EKRANLOGOWANIA_H
