#ifndef DODAWANIE_H
#define DODAWANIE_H

#include <QDialog>
#include <Baza/bramaznajomych.h>
#include <QListWidget>
#include <QString>
#include <iostream>
#include <QDebug>
#include "info.h"



namespace Ui {
class dodawanie;
}

class dodawanie : public QDialog
{
    Q_OBJECT
    
public:
    explicit dodawanie(QWidget *parent = 0, BramaZnajomych *bramaZnajomych=NULL);
    ~dodawanie();

private slots:
    //czytanie nicku
    void czytajNick(const QString &);
    //czytanie ID
    void czytajID(const QString &);
    //dodanie znajomego do listy
    void dodajZnajomego();
    void wyjscie();

signals:
    void zakoncz();
    
private:
    Ui::dodawanie *ui;
    Znajomy znajomy;
    BramaZnajomych *brama;

    info *oknoInformacji;
};

#endif // DODAWANIE_H
