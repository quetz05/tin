#include "grupowarozmowa.h"
#include "ui_grupowarozmowa.h"
#include "szyfrator.h"
#include <QDebug>
#include <unistd.h>

GrupowaRozmowa::GrupowaRozmowa(QWidget *parent, QList<Znajomy> lista, int socket) :
    QDialog(parent),
    ui(new Ui::GrupowaRozmowa)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->setupUi(this);

    gniazdo = socket;

    znajomi = lista;
    zaznaczonyDodaj = NULL;
    zaznaczonyUsun = NULL;

    connect(ui->pushAnuluj, SIGNAL(clicked()), this, SLOT(wyjdz()));
    connect(ui->pushTworz, SIGNAL(clicked()), this, SLOT(tworzRozmowe()));


    connect(ui->pushDodaj, SIGNAL(clicked()), this, SLOT(dodajDoRozmowy()));
    connect(ui->pushUsun, SIGNAL(clicked()), this, SLOT(usunZRozmowy()));
    connect(ui->listPierwotne, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(zaznaczenieDodaj(QListWidgetItem *)));
    connect(ui->listDodane, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(zaznaczenieUsun(QListWidgetItem *)));


    ui->pushDodaj->setEnabled(false);
    ui->pushUsun->setEnabled(false);

    odswiezListy();
}



GrupowaRozmowa::~GrupowaRozmowa()
{
    if(zaznaczonyDodaj != NULL)
         delete zaznaczonyDodaj;
    if(zaznaczonyUsun != NULL)
        delete zaznaczonyUsun;
    delete ui;
}

void GrupowaRozmowa::zaznaczenieDodaj(QListWidgetItem *znajomy)
{
    zaznaczonyDodaj = znajomy;
    ui->pushDodaj->setEnabled(true);
    ui->pushUsun->setEnabled(false);
}

void GrupowaRozmowa::zaznaczenieUsun(QListWidgetItem *znajomy)
{
    zaznaczonyUsun = znajomy;
    ui->pushUsun->setEnabled(true);
    ui->pushDodaj->setEnabled(false);
}

void GrupowaRozmowa::dodajDoRozmowy()
{
    int ID = QString(zaznaczonyDodaj->text()).section("|",1,1).toInt();


    znajomiDodani.push_back(znajomi.takeAt(znajdzZnajomego(znajomi,ID)));

    ui->pushDodaj->setEnabled(false);
    odswiezListy();

}

void GrupowaRozmowa::usunZRozmowy()
{
    int ID = QString(zaznaczonyUsun->text()).section("|",1,1).toInt();

    znajomi.push_back(znajomiDodani.takeAt(znajdzZnajomego(znajomiDodani,ID)));

    ui->pushUsun->setEnabled(false);

    odswiezListy();


}

int GrupowaRozmowa::znajdzZnajomego(QList <Znajomy> znaj, int ID)
{

    for(int i =0; i < znaj.length(); i++)
        if(znaj.at(i).second==ID)
            return i;

    return 0;

}

void GrupowaRozmowa::wyjdz()
{
    koniec();
}

void GrupowaRozmowa::tworzRozmowe()
{
    if(!znajomiDodani.empty())
    {
        for(int i = 0; i<znajomiDodani.length(); i++)
            IDs.push_back(znajomiDodani[i].second);

        Szyfrator szyfr;
        Wiadomosc wiad(ROZPOCZNIJ_ROZMOWE,0,"",gniazdo);
        unsigned int wielkosc;
        char *wiadomosc = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
            qDebug()<<"Błąd przy wysyłaniu wiadomosci o ID do rozmowy";
        }

    }

}


void GrupowaRozmowa::rozpocznijRozmowe(int id)
{

    for(int i = 0;i<IDs.length();i++)
    {
        Szyfrator szyfr;
        Wiadomosc wiad(DODAJ_DO_ROZMOWY,IDs[i],QString::number(id),gniazdo);
        unsigned int wielkosc;
        char *wiadomosc = szyfr.szyfruj(&wiad,0,&wielkosc);

        if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
            qDebug()<<"Błąd przy wysyłaniu id uzytkownika do nowej rozmowy";
        }
    }

}


void GrupowaRozmowa::odswiezListy()
{

    ui->listPierwotne->clear();
    ui->listDodane->clear();

    if(!znajomi.empty())
        for(int i = 0; i<znajomi.length(); i++)
            ui->listPierwotne->addItem(znajomi[i].first +"  "+"|"+QString::number(znajomi[i].second)+"|");


    if(!znajomiDodani.empty())
        for(int i = 0; i<znajomiDodani.length(); i++)
            ui->listDodane->addItem(znajomiDodani[i].first +"  "+"|"+QString::number(znajomiDodani[i].second)+"|");


}
