#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"
#include <unistd.h>
#include "szyfrator.h"
#include <QDebug>
#include <QKeyEvent>


oknoRozmowy::oknoRozmowy(QWidget *parent, int id, int socket, QString login) :
    QDialog(parent),
    ui(new Ui::oknoRozmowy)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    wiad = NULL;
    ID = id;
    gniazdo = socket;
    uzytkownik = login;

    ui->setupUi(this);

    QString title = "[ ";
    title.append(QString::number(id));
    title.append(" ] -- Super TIN - TIN : Rozmowa --");

    this->setWindowTitle(title);

    ui->liniaWiadomosci->setMaxLength(256);

    connect(ui->liniaWiadomosci, SIGNAL(textChanged(const QString &)), this, SLOT(wpisywanieWiadomosci(QString)));
    connect(ui->pushWyslij, SIGNAL(clicked()), this, SLOT(wyslij()));
    connect(ui->pushZakoncz, SIGNAL(clicked()), this, SLOT(zakoncz()));


}

oknoRozmowy::~oknoRozmowy()
{
    delete ui;
}


void oknoRozmowy::wpisywanieWiadomosci(const QString &text)
{
    wiadomosc = text;
    ui->licznikiZnakow->setText(QString::number(wiadomosc.length()) + QString(" / 256"));
}

void oknoRozmowy::wyslij()
{
    if(wiadomosc!="")
    {
        Szyfrator szyfr;
        QString data;
        data.append(uzytkownik);
        data.append(": ");
        data.append(wiadomosc);
        Wiadomosc wiad(WYSLIJ_WIADOMOSC,ID,data, gniazdo);
        unsigned int wielkosc;
        char *wiadom = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadom, wielkosc)==-1){
            qDebug()<<"Błąd przy wysyłaniu wiadomosci :(";
        }

        ui->liniaWiadomosci->clear();
        wiadomosc = "";
    }

}


void oknoRozmowy::zakoncz()
{
        Szyfrator szyfr2;
        QString data="";
        data.append("<font color='red'><b>>> Użytkownik :: <i>");
        data.append(uzytkownik);
        data.append(" </i> odłączył się z rozmowy. Pożegnajmy go brawami! <<</b></font>");
        Wiadomosc wiad2(WYSLIJ_WIADOMOSC,ID,data, gniazdo);
        unsigned int wielkosc2;
        char *wiadom2 = szyfr2.szyfruj(&wiad2,0,&wielkosc2);

        if(wiad2.wyslijDoSerwera(wiadom2, wielkosc2)==-1){
            qDebug()<<"Błąd przy kończeniu rozmowy";
        }

        Szyfrator szyfr;
        Wiadomosc wiad(ZAKONCZ_ROZMOWE,ID,QString(""), gniazdo);
        unsigned int wielkosc;
        char *wiadom = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadom, wielkosc)==-1){
            qDebug()<<"Błąd przy kończeniu rozmowy";
        }

       koniecRozmowy(ID);
}

void oknoRozmowy::wyswietlWiadomosc(QString wiadomosc)
{
    ui->oknoWiadomosci->append(wiadomosc);
}

void oknoRozmowy::keyPressEvent(QKeyEvent *keyevent)
{
    if(keyevent->key() == Qt::Key_Escape)
    {
        zakoncz();
    }
}




