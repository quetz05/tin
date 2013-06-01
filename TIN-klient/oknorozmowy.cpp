#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"

oknoRozmowy::oknoRozmowy(QWidget *parent, QString login, QString rozmowca, int socket) :
    QDialog(parent),
    ui(new Ui::oknoRozmowy)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    Wiadomosc wiadom( ROZPOCZNIJ_ROZMOWE,0,QString(""),gniazdo );
    wiadom.wyslijDoSerwera();

    /*@TODO funkcja read/ parę wątków*/



    loginTwoj = login;
    loginRozmowcy = rozmowca;
    gniazdo = socket;

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
        Wiadomosc wiadom( WYSLIJ_WIADOMOSC,ID,wiadomosc,gniazdo );
        wiadom.wyslijDoSerwera();

        //ui->oknoWiadomosci->append(loginTwoj + ": " + wiadomosc);
        ui->liniaWiadomosci->clear();
    }

}

void oknoRozmowy::zakoncz()
{

        Wiadomosc wiadom( ZAKONCZ_ROZMOWE,ID,QString(""),gniazdo );
        wiadom.wyslijDoSerwera();

       koniecRozmowy(loginRozmowcy);
}

