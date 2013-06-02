#include "oknorozmowy.h"
#include "ui_oknorozmowy.h"
#include <unistd.h>
#include "szyfrator.h"
#include <QDebug>


oknoRozmowy::oknoRozmowy(QWidget *parent, int id, int socket) :
    QDialog(parent),
    ui(new Ui::oknoRozmowy)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

   // Wiadomosc wiadom( ROZPOCZNIJ_ROZMOWE,0,QString(""),gniazdo );
    //wiadom.wyslijDoSerwera();
    wiad = NULL;

    /*@TODO funkcja read/ parę wątków*/


    ID = id;

    gniazdo = socket;



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
        Szyfrator szyfr;
        Wiadomosc wiad(WYSLIJ_WIADOMOSC,ID, wiadomosc, gniazdo);
        unsigned int wielkosc;
        char *wiadom = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(write(gniazdo,wiadom,wielkosc)==-1){
            qDebug()<<"Błąd przy wysyłaniu wiadomosci :(";
        }

        //ui->oknoWiadomosci->append(loginTwoj + ": " + wiadomosc);
        ui->liniaWiadomosci->clear();
    }

}

void oknoRozmowy::zakoncz()
{

       //wiad = new Wiadomosc ( ZAKONCZ_ROZMOWE,ID,QString(""),gniazdo );
       //wiad->wyslijDoSerwera();

       koniecRozmowy(ID);
}

