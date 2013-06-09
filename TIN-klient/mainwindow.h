#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
#include <wyszukiwarka.h>
#include <QProcess>
#include <QFileDialog>

#include "grupowarozmowa.h"
#include "ekranlogowania.h"
#include "serverconn.h"
#include "oknorozmowy.h"
#include "dodawanie.h"
#include "szyfrator.h"
#include "wysylaczplikow.h"
#include "odbieraczplikow.h"

 /**
    * @brief The MainWindow class
    * Klasa glownego okna aplikacji klienckiej zajmujaca sie tworzeniem 
    * nowych, pomniejszych okien i udostepniajaca wszystkie funkcje programu
    */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:


    //wylogowuje uzytkownika
    void wyloguj();
    //konczy dzialanie programu
    void zakoncz();
    //rozpoczyna wysylanie pliku
    void rozpocznijWysylanie();
    //wyswietla okno dodawania znajomego
    void dodajZnajomego();
    //usuwa znajomego z listy
    void usunZnajomego();
    //zaznacza konkretnego znajomego
    void zaznaczenieZnajomego(QListWidgetItem *znajomy);
    void zakonczDodawanie();
    void zakonczRozmowe(int id);
    void wczytajZnajomych();
    void rozpocznijGrupRozmowe();
    void zakonczGrupRoz();
    void zaloguj(const QString&login, const int id);
    void elCzyRejestracja(int id) {emit elSIGczyRejestracja(id);}
    void elCzyZaloguj(int id) {emit elSIGczyZaloguj(id);}
    void nowaRozmowa(int id);
    void twojaNowaRozmowa(int id);
    void odbierajWiadomosc(int id, QString wiadomosc);
    void czyIstnieje(const int);
    void wyszukiwarkaZnajomych();
    void serwerNiezyje();

    void plikOdbiorStart(int, QString);
    void plikOdbiorTransfer(char*, int);
    void plikOdbiorKoniec();
    void plikWysylStart();
    void plikWysylTransfer();
    void plikWysylKoniec();



public slots:
    void koniecInfo() {delete oknoInformacji; oknoInformacji = NULL;}
    void theEnd();

    
public:
    explicit MainWindow(QWidget *parent = 0, QString login="", int socket=0);
    ~MainWindow();
    ServerConn *con;

private:

    Ui::MainWindow *ui;
    QListWidgetItem *zaznaczonyZnajomy;
    dodawanie *doda;
    QMap <int,oknoRozmowy*> oknaRozmowy;
    QString uzytkownik;
    info *oknoInformacji;
    BramaZnajomych *bramaZnajomych;
    QList <Znajomy> znajomi;
    QFileDialog *oknoWysylania;
    int gniazdo;
    GrupowaRozmowa *grRozmowa;
    ekranLogowania *el;
    int uzytkownikID;
    WysylaczPlikow *wp;
    OdbieraczPlikow *op;


signals:
    //sygnal do ekranu logowania
    void elSIGczyRejestracja(int);
    //sygnal do okna rozmowy
    void elSIGCzyRozmowa();
    void elSIGCzyRozmowaGrup();
    //sygnal do zalogowania
    void elSIGczyZaloguj(int);
    void grTwojaNowaRozmowa(int);
    void odSIGczyIstnieje(const int);
    void zakonczServerConn();

};

#endif // MAINWINDOW_H
