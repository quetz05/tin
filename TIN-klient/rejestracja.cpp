#include "rejestracja.h"
#include "ui_rejestracja.h"
#include <QDebug>
#include <netinet/in.h>
#include <unistd.h>


Rejestracja::Rejestracja(QWidget *parent, int socket) :
    QDialog(parent),
    ui(new Ui::Rejestracja)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->setupUi(this);

    login = "";
    haslo = "";
    haslo2 = "";
    gniazdo = socket;

    oknoInformacji = NULL;
    wiad = NULL;

    connect(ui->pushRejestruj, SIGNAL(clicked()), this, SLOT(rejestruj()));
    connect(ui->pushAnuluj, SIGNAL(clicked()), this, SLOT(wyjscie()));

    connect(ui->poleNick, SIGNAL(textChanged(const QString &)), this, SLOT(czytajNick(QString)));
    connect(ui->polePass, SIGNAL(textChanged(const QString &)), this, SLOT(czytajHaslo(QString)));
    connect(ui->polePass2, SIGNAL(textChanged(const QString &)), this, SLOT(czytajHaslo2(QString)));


    ui->polePass->setEchoMode(QLineEdit::Password);
    ui->polePass->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    ui->polePass2->setEchoMode(QLineEdit::Password);
    ui->polePass2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

}

Rejestracja::~Rejestracja()
{
    delete oknoInformacji;
    delete ui;
}

void Rejestracja::rejestruj()
{
   /* if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }*/

   /* if(wiad!=NULL)
    {
        delete wiad;
        wiad=NULL;
    }*/

    if(login=="")
        oknoInformacji = new info(this,"Nie no, bez nicku to nie ma rejestracji!",false);

    else if(haslo=="" || haslo2=="")
        oknoInformacji = new info(this,"Tak bez hasła? To prawie jak paradowanie nago w miejscu publicznym!",false);

    else if(haslo!=haslo2)
        oknoInformacji = new info(this,"Oba hasła niepodobne są do siebie... wpisz je proszę raz jeszcze.",false);

    else
    {
        wiad = new Wiadomosc( REJESTRUJ,2*login.length(),login + haslo,gniazdo );
        wiad->wyslijDoSerwera();
    }
}

void Rejestracja::czytajHaslo(const QString &pass)
{
    haslo = pass;

}

void Rejestracja::czytajHaslo2(const QString &pass)
{
    haslo2 = pass;

}

void Rejestracja::czytajNick(const QString &log)
{
    login = log;
}

void Rejestracja::wyjscie()
{

    login = "";
    haslo="";
    haslo2="";
    ui->polePass->clear();
    ui->polePass2->clear();
    ui->poleNick->clear();
    emit zakoncz();

}

void Rejestracja::wynikRejestracji(int wynik)
{

    /*if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }*/

    if (!wynik==0)
    {
        oknoInformacji = new info(this,QString("Rejestracja przebiegła pomyślnie! Twoje ID to") + QString(wynik) + QString("Witamy w ekipie!"),true);

        wyjscie();
    }
    else
        oknoInformacji = new info(this,"Ten nick jest już zajęty... Wybierz inny.",false);
}
