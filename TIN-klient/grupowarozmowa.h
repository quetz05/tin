#ifndef GRUPOWAROZMOWA_H
#define GRUPOWAROZMOWA_H

#include <QDialog>
#include <QListWidgetItem>
#include "Baza/bramaznajomych.h"

namespace Ui {
class GrupowaRozmowa;
}
/**
* @brief the GrupowaRozmowa class
* Pozwala tworzyc grupowe rozmowy
*/
class GrupowaRozmowa : public QDialog
{
    Q_OBJECT

public slots:
    void rozpocznijRozmowe(int);


private slots:

    void wyjdz();
    /**
    * @brief tworzRozmowe
    * Wysyla sygnal do serwera o stworzenie nowej rozmowy
    */
    void tworzRozmowe();
    /**
    * @brief dodajDoRozmowy
    * dodaje znajomego do listy użytkowników w przyszlej rozmowie
    */
    void dodajDoRozmowy();
        /**
    * @brief dodajDoRozmowy
    * usuwa znajomego z listy użytkowników w przyszlej rozmowie
    */
    void usunZRozmowy();
    void zaznaczenieDodaj(QListWidgetItem*);
    void zaznaczenieUsun(QListWidgetItem*);

    
public:
    explicit GrupowaRozmowa(QWidget *parent = 0, QList <Znajomy> lista = *(new QList <Znajomy>), int socket = 0);
    ~GrupowaRozmowa();
    
private:
    Ui::GrupowaRozmowa *ui;
    QListWidgetItem *zaznaczonyDodaj;
    QListWidgetItem *zaznaczonyUsun;
    QList <Znajomy> znajomi;
    QList <Znajomy> znajomiDodani;
    int gniazdo;
    int znajdzZnajomego(QList <Znajomy> znaj, int ID);
    void odswiezListy();
    QList <int> IDs;


signals:
    void koniec();
};

#endif // GRUPOWAROZMOWA_H
