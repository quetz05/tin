#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
#include <wyszukiwarka.h>
#include <dodawanie.h>
#include <QProcess>

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
    void rozpocznijRozmowe(int *listaUczestnikow);
    //rozpoczyna wysylanie pliku
    void rozpocznijWysylanie(int *listaUczestnikow);
    //wyswietla okno dodawania znajomego
    void dodajZnajomego();
    //usuwa znajomego z listy
    void usunZnajomego();
    //zaznacza konkretnego znajomego
    void zaznaczenieZnajomego(QListWidgetItem *znajomy);



    
public:
    explicit MainWindow(QWidget *parent = 0, QString login="");
    ~MainWindow();


        BramaZnajomych *bramaZnajomych;
        QList <Znajomy> znajomi;
        void wczytajZnajomych();
        info *oknoInformacji;
    
private:



    Ui::MainWindow *ui;
    wyszukiwarka *wysz;
    QListWidgetItem *zaznaczonyZnajomy;
    dodawanie *doda;



};

#endif // MAINWINDOW_H
