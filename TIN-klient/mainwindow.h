#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <iostream>
#include <QDebug>
#include <wyszukiwarka.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

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



    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    wyszukiwarka *wysz;
};

#endif // MAINWINDOW_H
