#include "ekranlogowania.h"
#include "ui_ekranlogowania.h"


ekranLogowania::ekranLogowania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ekranLogowania)
{
    ui->setupUi(this);

    login = "";
    dostep - false;

    oknoInformacji = NULL;

    connect(ui->pushZakoncz, SIGNAL(clicked()), this, SLOT(zakoncz()));
    connect(ui->pushZaloguj, SIGNAL(clicked()), this, SLOT(zaloguj()));
    connect(ui->pushRejestruj, SIGNAL(clicked()), this, SLOT(rejestruj()));


    connect(ui->textPass, SIGNAL(textChanged(const QString &)), this, SLOT(czytajHaslo(QString)));
    connect(ui->textLogin, SIGNAL(textChanged(const QString &)), this, SLOT(czytajLogin(QString)));

    ui->textPass->setEchoMode(QLineEdit::Password);
    ui->textPass->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);

    ui->pushRejestruj->setEnabled(false);
}

ekranLogowania::~ekranLogowania()
{
    oknoInformacji = NULL;
    delete oknoInformacji;
    delete ui;
}

void ekranLogowania::zakoncz()
{

    QApplication::exit();
}

void ekranLogowania::zaloguj()
{
    if(login=="")
        oknoInformacji = new info(this, "Nie wstydź się! Wpisz login.");

    else if(haslo=="")
        oknoInformacji = new info(this, "You shall not PASS!");

    else if(login!="" && haslo!="")
    {

            dostep = true;

             MainWindow *w = new MainWindow (0,login);

             this->hide();
             w->show();

             this->~ekranLogowania();

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


}
