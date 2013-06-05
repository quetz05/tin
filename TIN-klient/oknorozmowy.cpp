#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"
#include <unistd.h>
#include "szyfrator.h"
#include <QDebug>


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

        //ui->oknoWiadomosci->append(loginTwoj + ": " + wiadomosc);
        ui->liniaWiadomosci->clear();
        wiadomosc = "";
    }

}


void oknoRozmowy::zakoncz()
{

       //wiad = new Wiadomosc ( ZAKONCZ_ROZMOWE,ID,QString(""),gniazdo );
       //wiad->wyslijDoSerwera();

       koniecRozmowy(ID);
}

void oknoRozmowy::wyswietlWiadomosc(QString wiadomosc)
{
    ui->oknoWiadomosci->append(wiadomosc);
}


