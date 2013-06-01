#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"

oknoRozmowy::oknoRozmowy(QWidget *parent, QString login, QList<QString> rozmowca, int socket) :
    QDialog(parent),
    ui(new Ui::oknoRozmowy)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

   // Wiadomosc wiadom( ROZPOCZNIJ_ROZMOWE,0,QString(""),gniazdo );
    //wiadom.wyslijDoSerwera();
    wiad = NULL;

    /*@TODO funkcja read/ parę wątków*/



    loginTwoj = login;
    rozmowcy = rozmowca;
    gniazdo = socket;


    QString tytul;

    for(int i = 0; rozmowcy.length();i++)
        tytul = tytul + rozmowcy[i] + ",";

    this->setWindowTitle(tytul);

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

       wiad = new Wiadomosc ( ZAKONCZ_ROZMOWE,ID,QString(""),gniazdo );
       wiad->wyslijDoSerwera();

       koniecRozmowy(loginRozmowcy);
}

