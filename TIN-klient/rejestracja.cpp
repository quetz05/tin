#include "rejestracja.h"
#include "ui_rejestracja.h"
#include <QDebug>
#include <netinet/in.h>
#include <unistd.h>
#include <szyfrator.h>


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
    wyslij = NULL;

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
    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if(login=="")
        oknoInformacji = new info(this,"Nie no, bez nicku to nie ma rejestracji!",false);

    else if(haslo=="" || haslo2=="")
        oknoInformacji = new info(this,"Tak bez hasła? To prawie jak paradowanie nago w miejscu publicznym!",false);

    else if(haslo!=haslo2)
        oknoInformacji = new info(this,"Oba hasła niepodobne są do siebie... wpisz je proszę raz jeszcze.",false);

    else
    {
        if(wyslij)
        {
            delete wyslij;
            wyslij = NULL;
        }

        QString s = "";
        s.append(login);
        s.append(haslo);

        wyslij = new Wyslij(REJESTRUJ, login.length(),s ,gniazdo,NULL);
        wyslij->wyslij();

        /*Szyfrator szyfr;
        QString s = "";
        s.append(login);
        s.append(haslo);
        Wiadomosc wiad(REJESTRUJ,login.length(),s,gniazdo );
        unsigned int wielkosc;
        char *wiadomosc = szyfr.szyfruj(&wiad,NULL,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
            qDebug()<<"Błąd przy rejestracji";
        }*/
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

    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if (!wynik==0)
    {
        QString inf = "";
        inf.append("Rejestracja przebiegła pomyślnie! Twoje ID to ");
        inf.append(QString::number(wynik));
        inf.append(". Witamy w ekipie!");

        oknoInformacji = new info(this,inf,true);

        wyjscie();
    }
    else
        oknoInformacji = new info(this,"Ten nick jest już zajęty... Wybierz inny.",false);
}
