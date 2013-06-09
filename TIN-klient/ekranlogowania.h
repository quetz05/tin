#ifndef EKRANLOGOWANIA_H
#define EKRANLOGOWANIA_H

#include <QDialog>
#include <QString>
#include "info.h"
#include "rejestracja.h"
#include "../wyslij.h"

namespace Ui {
class ekranLogowania;
}

/**
* @brief The ekranLogowania class
* Klasa okna pozwalajaca na zalogowanie sie na swoje konto
*
*/
class ekranLogowania : public QDialog
{
    Q_OBJECT


private slots:

    /**
    * @brief czytajLogin
    * czyta login z pola tekstowego
    * */
    void czytajLogin(QString);
    /**
    * @brief czytajHaslo
    * czyta hasło z pola tekstowego
    * */
    void czytajHaslo(QString);
    /**
    * @brief zakoncz
    * konczy program
    * */
    void zakoncz();
    /**
    * @brief  zaloguj
    * wysyła wiadomość do serwera w celu zalogowania uzytkownika
    * */
    void zaloguj();
    /**
    * @brief rejestruj
    * wysyła wiadomość do serwera w celu rejestracji
    * */
    void rejestruj();
    /**
    * @brief zakonczRejestracje
    * zamyka okno rejestracji (chowa de facto)
    * */
    void zakonczRejestracje();

public slots:
    /**
    * @brief rejCzyRejestracja
    * przesyła sygnał do okna rejestracji z wynikiem operacji (ID)
    * */
    void rejCzyRejestracja(int id) {emit SIGczyRejestracja(id);}
    /**
    * @brief sprawdzZaloguj
    * sprawdza czy zalogowanie jest mozliwe (poprawne)
    * */
    void sprawdzZaloguj(int);
     /**
    * @brief koniecInfo
    * niszczy okno informacji
    * */
    void koniecInfo() {delete oknoInformacji; oknoInformacji = NULL;}

signals:
    void logowanie(const QString&,const int);
    void SIGczyRejestracja(int);
    
public:
    explicit ekranLogowania(QWidget *parent = 0, int socket=0);
    ~ekranLogowania();
    /**
    * @brief pobierzLogin
    * pobiera login
    * */
    QString pobierzLogin();
    
private:
    QString login;
    QString haslo;
    //Wiadomosc *wiad;
    Rejestracja *rej;
    info *oknoInformacji;
    int gniazdo;
    Ui::ekranLogowania *ui;
    Wyslij *wyslij;
};

#endif // EKRANLOGOWANIA_H
