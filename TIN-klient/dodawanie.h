#ifndef DODAWANIE_H
#define DODAWANIE_H

#include <QDialog>
#include "Baza/bramaznajomych.h"
#include <QListWidget>
#include <QString>
#include <iostream>
#include <QDebug>
#include "info.h"



namespace Ui {
class dodawanie;
}

/**
* @brief The dodawanie class
* Klasa okna pozwalajaca na dodawanie nowych znajomych do lokalnej losty kontaktów
*
*/
class dodawanie : public QDialog
{
    Q_OBJECT
    
public:
    explicit dodawanie(QWidget *parent = 0, BramaZnajomych *bramaZnajomych=NULL, int socket=0, int id=0);
    ~dodawanie();

private slots:
    /**
    * @brief czytajNick
    * Slot czytajacy nick z pola tekstowego do QStringa
    */
    void czytajNick(const QString &);
    /**
    * @brief czytajID
    * Slot czytajacy ID z pola tekstowego do QStringa
    */
    void czytajID(const QString &);
      /**
    * @brief dodajZnajomego
    * Slot dodajacy znajomego do lokalnej bazy danych konta
    */
    void dodajZnajomego();
    /**
    * @brief wysjcie
    * Metoda zamykajaca okno
    *
    */
    void wyjscie();

public slots:
    /**
    * @brief koniecInfo
    * Slot zamykajacy i niszczacy okno informacyjne
    */
    void koniecInfo() {delete oknoInformacji; oknoInformacji = NULL;}
    /**
    * @brief sprawdzenieIstnienie
    * Slot sprawdzający czy użytkownik o danym id istnieje po wcześniejszym sygnale z serwera
    */
    void sprawdzenieIstnienie(const int id);

signals:
    void zakoncz();
    
private:
    Ui::dodawanie *ui;
    Znajomy znajomy;
    BramaZnajomych *brama;
    int gniazdo;
    info *oknoInformacji;
    int uzytkownikID;
};

#endif // DODAWANIE_H
