#include "ekranlogowania.h"
#include "ui_ekranlogowania.h"
#include <QDebug>
#include "szyfrator.h"
#include <unistd.h>


ekranLogowania::ekranLogowania(QWidget *parent, int socket) :
    QDialog(parent),
    ui(new Ui::ekranLogowania)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->setupUi(this);

    gniazdo = socket;

    login = "";

    oknoInformacji = NULL;
    rej = new Rejestracja(0,gniazdo);

    wiad = NULL;

    connect(this,SIGNAL(SIGczyRejestracja(int)),rej,SLOT(wynikRejestracji(int)));

    connect(ui->pushZakoncz, SIGNAL(clicked()), this, SLOT(zakoncz()));
    connect(ui->pushZaloguj, SIGNAL(clicked()), this, SLOT(zaloguj()));
    connect(ui->pushRejestruj, SIGNAL(clicked()), this, SLOT(rejestruj()));

    connect(ui->textPass, SIGNAL(textChanged(const QString &)), this, SLOT(czytajHaslo(QString)));
    connect(ui->textLogin, SIGNAL(textChanged(const QString &)), this, SLOT(czytajLogin(QString)));

    ui->textPass->setEchoMode(QLineEdit::Password);
    ui->textPass->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

}

ekranLogowania::~ekranLogowania()
{
   /* if(oknoInformacji)
        delete oknoInformacji;*/

    delete ui;
}

void ekranLogowania::zakoncz()
{

    wiad = new Wiadomosc(ODLACZ_UZYTKOWNIKA,0,"",gniazdo);
    wiad->wyslijDoSerwera();

    QApplication::exit();
}

void ekranLogowania::zaloguj()
{
    if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if(login=="")
        oknoInformacji = new info(this, "Nie wstydź się! Wpisz login.");

    else if(haslo=="")
        oknoInformacji = new info(this, "You shall not PASS!");

    else if(login!="" && haslo!="")
    {

        Szyfrator szyfr;
        QString s = "";
        s.append(login);
        s.append(haslo);
        Wiadomosc wiad(LOGUJ_UZYTKOWNIKA, login.length(),s,gniazdo);
        unsigned int wielkosc;
        char *wiadomosc = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
            qDebug()<<"Błąd przy logowaniu";
        }

    }

}


void ekranLogowania::czytajHaslo(QString pass)
{
    haslo = pass;

}


void ekranLogowania::czytajLogin(QString log)
{

    login = log;
}

QString ekranLogowania::pobierzLogin()
{
    return login;
}

void ekranLogowania::rejestruj()
{
   connect(rej, SIGNAL(zakoncz()), this, SLOT(zakonczRejestracje()));
   rej->show();
}

void ekranLogowania::zakonczRejestracje()
{
    rej->hide();
}

void ekranLogowania::sprawdzZaloguj(int id)
{
    qDebug() << "WIADOMOSC WRACA!";
    qDebug() << id;

    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    if (!id==0)
    {

        oknoInformacji = new info(this,QString("Witaj ponownie ") + login,true);

        emit logowanie(login);

    }
    else
    {
        oknoInformacji = new info(this,"Błędny login lub hasło - spróbuj ponownie.",false);
        haslo="";
        login="";
        ui->textLogin->clear();
        ui->textPass->clear();


    }
}
