#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
#include <wyszukiwarka.h>
#include <dodawanie.h>
#include <QProcess>
#include "oknorozmowy.h"
#include <QFileDialog>
#include "grupowarozmowa.h"
#include "ekranlogowania.h"


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
    //wyswietla okno do wyszukiwania znajomych
    void wyszukiwarkaZnajomych();
    //rozpoczyna rozmowe
    void rozpocznijRozmowe();
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

    void rozpocznijGrupWysylanie();
    void zakonczGrupRoz();
    void tworzGrupRoz(const QList<int> &);

    void zaloguj(const QString&login);
    
public:
    explicit MainWindow(QWidget *parent = 0, QString login="", int socket=0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    //wyszukiwarka *wysz;
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




};

#endif // MAINWINDOW_H
