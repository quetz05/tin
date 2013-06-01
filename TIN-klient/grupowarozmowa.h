#ifndef GRUPOWAROZMOWA_H
#define GRUPOWAROZMOWA_H

#include <QDialog>
#include <QListWidgetItem>
#include "Baza/bramaznajomych.h"

namespace Ui {
class GrupowaRozmowa;
}

class GrupowaRozmowa : public QDialog
{
    Q_OBJECT

private slots:

    void wyjdz();
    void tworzRozmowe();
    void dodajDoRozmowy();
    void usunZRozmowy();
    void zaznaczenieDodaj(QListWidgetItem*);
    void zaznaczenieUsun(QListWidgetItem*);

    
public:
    explicit GrupowaRozmowa(QWidget *parent = 0, QList <Znajomy> lista = *(new QList <Znajomy>));
    ~GrupowaRozmowa();
    
private:
    Ui::GrupowaRozmowa *ui;
    QListWidgetItem *zaznaczonyDodaj;
    QListWidgetItem *zaznaczonyUsun;
    QList <Znajomy> znajomi;
    QList <Znajomy> znajomiDodani;

    int znajdzZnajomego(QList <Znajomy> znaj, int ID);
    void odswiezListy();


signals:
    void koniec();
    void tworz(const QList<int>&);
};

#endif // GRUPOWAROZMOWA_H
