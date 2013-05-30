#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"

oknoRozmowy::oknoRozmowy(QWidget *parent, QString login, QString rozmowca) :
    QDialog(parent),
    ui(new Ui::oknoRozmowy)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    loginTwoj = login;
    loginRozmowcy = rozmowca;

    this->setWindowTitle(loginRozmowcy);

    ui->setupUi(this);


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
        ui->oknoWiadomosci->append(loginTwoj + ": " + wiadomosc);
        ui->liniaWiadomosci->clear();
    }

}

void oknoRozmowy::zakoncz()
{
       koniecRozmowy(loginRozmowcy);
}

