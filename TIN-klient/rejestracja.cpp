#include "rejestracja.h"
#include "ui_rejestracja.h"

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
    if(login=="")
        oknoInformacji = new info(this,"Nie no, bez nicku to nie ma rejestracji!",false);

    else if(haslo=="" || haslo2=="")
        oknoInformacji = new info(this,"Tak bez hasła? To prawie jak paradowanie nago w miejscu publicznym!",false);

    else if(haslo!=haslo2)
        oknoInformacji = new info(this,"Oba hasła niepodobne są do siebie... wpisz je proszę raz jeszcze.",false);



    else
    {
        //Wiadomosc wiadom( REJESTRUJ,login.length(),login + haslo,gniazdo );
        //wiadom.wyslijDoSerwera();



        //oknoInformacji = new info(this,"Rejestracja przebiegła pomyślnie! Witamy w ekipie!",true);
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
