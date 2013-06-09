#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QDebug>
#include "wysylaczplikow.h"
#include <QThreadPool>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, QString login, int socket) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    gniazdo = socket;
    uzytkownik = login;
    zaznaczonyZnajomy = NULL;
    bramaZnajomych = NULL;
    grRozmowa = NULL;
    doda = NULL;
    oknoWysylania= new QFileDialog(this);
    oknoInformacji = NULL;

    con = new ServerConn(NULL,socket);


    el = new ekranLogowania(this,socket);
    el->show();


    //ekran logowania
    connect(el, SIGNAL(logowanie(const QString&, const int)), this, SLOT(zaloguj(QString,int)));
    connect(this, SIGNAL(elSIGczyRejestracja(int)), el, SLOT(rejCzyRejestracja(int)));
    connect(this, SIGNAL(elSIGczyZaloguj(int)), el, SLOT(sprawdzZaloguj(int)));


    //serverconnect
    connect(con, SIGNAL(czyRejestracja(int)), this, SLOT(elCzyRejestracja(int)));
    connect(con, SIGNAL(czyZaloguj(int)), this, SLOT(elCzyZaloguj(int)));
    connect(con, SIGNAL(nowaRozmowa(int)), this, SLOT(twojaNowaRozmowa(int)));
    connect(con, SIGNAL(odbiorRozmowy(int)), this, SLOT(nowaRozmowa(int)));
    connect(con, SIGNAL(odebranaWiadomosc(int,QString)), this, SLOT(odbierajWiadomosc(int, QString)));
    connect(con, SIGNAL(czyIstnieje(const int)),this,SLOT(czyIstnieje(int)));
    connect(con, SIGNAL(niezywySerwer()),this,SLOT(serwerNiezyje()));
    connect(con, SIGNAL(plikObiorStart(int,QString)), this, SLOT(plikOdbiorStart(int,QString)));
    connect(con, SIGNAL(plikOdbiorTransfer(char*, int)), this, SLOT(plikOdbiorTransfer(char*, int)));
    connect(con, SIGNAL(plikOdbiorKoniec()), this, SLOT(plikOdbiorKoniec()));
    connect(con, SIGNAL(plikWysylStart()), this, SLOT(plikWysylStart()));

    ui->setupUi(this);


    connect(ui->pushWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijWysylanie()));

    connect(ui->pushGrupRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijGrupRozmowe()));

    connect(ui->pushSzukajZnajomych, SIGNAL(clicked()), this, SLOT(wyszukiwarkaZnajomych()));

    connect(ui->actionZakoncz, SIGNAL(triggered()), this, SLOT(zakoncz()));
    connect(ui->actionWyloguj, SIGNAL(triggered()), this, SLOT(wyloguj()));

    connect(ui->pushDodaj, SIGNAL(clicked()), this, SLOT(dodajZnajomego()));
    connect(ui->pushUsun, SIGNAL(clicked()), this, SLOT(usunZnajomego()));
    connect(ui->listaZnajomych, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(zaznaczenieZnajomego(QListWidgetItem *)));



    //wyswietlanie loga
    QGraphicsScene *scene =  new QGraphicsScene();
    QPixmap pixmap(":/images/tin.jpg");
    scene->addPixmap(pixmap);
    ui->logoView->setScene(scene);
    ui->logoView->show();



    ui->pushWyslijPlik->setEnabled(false);
    ui->pushUsun->setEnabled(false);


    ui->pushGrupWyslijPlik->setEnabled(false);
}

MainWindow::~MainWindow()
{

    if(zaznaczonyZnajomy)
        delete zaznaczonyZnajomy;
    if(doda)
        delete doda;
    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;

    }

    delete ui;
}


void MainWindow::wyloguj()
{

    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::zaloguj(const QString &login,const int id)
{

    el->hide();

    uzytkownik = login;
    uzytkownikID = id;

    QString tytul = "";
    tytul.append(login);
    tytul.append(" (");
    tytul.append(QString::number(id));
    tytul.append(") - Super TIN - TIN");
    this->setWindowTitle(tytul);

    bramaZnajomych = new BramaZnajomych(QString(uzytkownik));
    doda = new dodawanie(this,bramaZnajomych,gniazdo,uzytkownikID);

    //wczytywanie listy znajomych
    wczytajZnajomych();

    this->show();

    if(oknoInformacji)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    oknoInformacji = new info(this,QString("Witaj ponownie ") + login,true);
}

void MainWindow::zakoncz()
{
    QApplication::exit();
}


void MainWindow::rozpocznijWysylanie()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wybierz Plik", "", "*.*");
    if (fileName.length() != 0) {

        QFile *plik = new QFile(fileName);
        plik->open(QIODevice::ReadOnly);
/*        if (plik.size() > 21000) {

            if (oknoInformacji)
                delete oknoInformacji;

            oknoInformacji = new info(this, QString("Za duży plik! Proszę wybrać plik o rozmiarze do 20kb!"), false);
        } else {*/

            wp = new WysylaczPlikow(plik, gniazdo, QString(zaznaczonyZnajomy->text()).section("|",1,1).toInt(), NULL);

            unsigned int subIndex = fileName.lastIndexOf('/') + 1;
            qDebug() << "subIndex == " << subIndex;

            fileName = fileName.right(fileName.length() - subIndex);

            qDebug() << "fileName == " << fileName;

            Szyfrator szyfr;
            Wiadomosc wiad(PLIK_POCZATEK, uzytkownikID, fileName, gniazdo);
            unsigned int rozmiar;
            char *dane = szyfr.szyfruj(&wiad, NULL, &rozmiar);
            wiad.wyslijDoSerwera(dane, rozmiar);

            delete dane;

        //}
    }
}

void MainWindow::dodajZnajomego()
{

    connect(doda, SIGNAL(zakoncz()), this, SLOT(zakonczDodawanie()));
    connect(this, SIGNAL(odSIGczyIstnieje(const int)),doda, SLOT(sprawdzenieIstnienie(int)));

    doda->show();

}

void MainWindow::usunZnajomego()
{

    if(zaznaczonyZnajomy!=NULL)
    {
        int ID = QString(zaznaczonyZnajomy->text()).section("|",1,1).toInt();

        if(!bramaZnajomych->usunZnajomego(ID))
        {
            if(oknoInformacji)
            {
                delete oknoInformacji;
                oknoInformacji = NULL;
            }

            oknoInformacji = new info(this,"Wystąpił problem przy usuwaniu znajomego. To nie moja wina! Twórcy coś pokopali...",false);

        }
        else
        {
            zaznaczonyZnajomy=NULL;

            wczytajZnajomych();
            ui->pushUsun->setEnabled(false);
            ui->pushWyslijPlik->setEnabled(false);
        }
    }
}

void MainWindow::zaznaczenieZnajomego(QListWidgetItem *znajomy)
{
    zaznaczonyZnajomy = znajomy;
    ui->pushUsun->setEnabled(true);

    ui->pushWyslijPlik->setEnabled(true);

}

void MainWindow::wczytajZnajomych()
{
    ui->listaZnajomych->clear();

    if(bramaZnajomych->getListaZnajomych().empty()==false)
    {
        znajomi = bramaZnajomych->getListaZnajomych();

        for(int i = 0; i<znajomi.length(); i++)
        {
            ui->listaZnajomych->addItem(znajomi[i].first +"  "+"|"+QString::number(znajomi[i].second)+"|");
        }
    }
}

void MainWindow::zakonczDodawanie()
{
    wczytajZnajomych();
    doda->hide();
}

void MainWindow::zakonczRozmowe(int id)
{
    Szyfrator szyfr;
    Wiadomosc wiad(ZAKONCZ_ROZMOWE,id,"",gniazdo);
    unsigned int wielkosc;
    char *wiadomosc = szyfr.szyfruj(&wiad,0,&wielkosc);

    if(wiad.wyslijDoSerwera(wiadomosc, wielkosc)==-1){
        qDebug()<<"Błąd przy wysyłaniu wiadomosci :(";
    }

    delete [] wiadomosc;

    QMap <int, oknoRozmowy*>::Iterator it = oknaRozmowy.find(id);
    delete oknaRozmowy.value(id);
    oknaRozmowy.erase(it);
}

void MainWindow::rozpocznijGrupRozmowe()
{
    if (grRozmowa != NULL)
        delete grRozmowa;

    znajomi = bramaZnajomych->getListaZnajomych();

    grRozmowa = new GrupowaRozmowa(this, znajomi, gniazdo);

    connect(this, SIGNAL(grTwojaNowaRozmowa(int)), grRozmowa, SLOT(rozpocznijRozmowe(int)));

    connect(grRozmowa, SIGNAL(koniec()), this, SLOT(zakonczGrupRoz()));

    grRozmowa->show();

}

void MainWindow::zakonczGrupRoz()
{
    delete grRozmowa;
    grRozmowa = NULL;
}


void MainWindow::nowaRozmowa(int id)
{

    if(oknaRozmowy.count(id)==0)
    {

        oknaRozmowy.insert(id,new oknoRozmowy(this,id,gniazdo,uzytkownik));

        connect(oknaRozmowy.value(id), SIGNAL(koniecRozmowy(int)), this, SLOT(zakonczRozmowe(int)));

        oknaRozmowy.value(id)->show();
    }
}

void MainWindow::twojaNowaRozmowa(int id)
{
    emit grTwojaNowaRozmowa(id);
}

void MainWindow::odbierajWiadomosc(int id, QString wiadomosc)
{
    if(oknaRozmowy.count(id)==1)
        oknaRozmowy.value(id)->wyswietlWiadomosc(wiadomosc);
}

void MainWindow::czyIstnieje(const int odp)
{

    emit odSIGczyIstnieje(odp);

}

void MainWindow::wyszukiwarkaZnajomych()
{
    if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    oknoInformacji = new info(this,"Sorry, but this feature has not yet been implemented",false);
}

void MainWindow::serwerNiezyje()
{
    if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    oknoInformacji = new info(this,"Świętej pamięci serwer nie żyje... Program ulegnie zamknięciu.",false);
    oknoInformacji->exec();

    QApplication::exit();
}

void MainWindow::plikOdbiorStart(int idZrodla, QString nazwa) {

    qDebug() << "zaczynam odbior pliku";

    Szyfrator szyfr;
    Wiadomosc *wiad;
    char *dane;
    unsigned int rozmiar;

    QString pytanie = "Czy chcesz odebrać plik <b>";
    pytanie.append(nazwa);
    pytanie.append(" </b> od użytkownika <b> ");
    pytanie.append(idZrodla);
    pytanie.append(" </b>?");

    QString nazwaDysk;

    if (QMessageBox::Yes == QMessageBox::question(this, "Przesył pliku", pytanie, QMessageBox::Yes|QMessageBox::No)) {

        wiad = new Wiadomosc(PLIK_CHCE, idZrodla, QString(""), gniazdo);
        nazwaDysk = QFileDialog::getSaveFileName(this, "Zapisz Plik", nazwa, "");

        qDebug() << "nazwaDysk == " << nazwaDysk;


    }
    else
        wiad = new Wiadomosc(PLIK_NIECHCE, idZrodla, QString(""), gniazdo);


    dane = szyfr.szyfruj(wiad, NULL, &rozmiar);
    wiad->wyslijDoSerwera(dane, rozmiar);

    op = new OdbieraczPlikow(nazwaDysk, this);

    delete dane;
    delete wiad;

}

void MainWindow::plikOdbiorTransfer(char* paczka, int size) {

//    qDebug() << "plik partia";

    if (op != NULL) {
        QByteArray *partia = new QByteArray(QByteArray::fromRawData(paczka, size));
        op->nowaPartia(partia);
    } else {
        qDebug() << "te JUJU to wogóle niedobre...";
    }

}

void MainWindow::plikOdbiorKoniec() {

    qDebug() << "plik koniec odbioru";

    delete op;

    if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    oknoInformacji = new info(this,"Melduje wykonanie zadania, plik odebrany.",true);
    oknoInformacji->show();

}

// jak tu jestesmy to znaczy ze przyszlo PLIK_CHCE
void MainWindow::plikWysylStart() {

    qDebug() << "zaczynam slac";

    QThreadPool::globalInstance()->start(wp);

}

void MainWindow::plikWysylTransfer() {
//ew. update paska postepu
}

void MainWindow::plikWysylKoniec() {

    if(oknoInformacji!=NULL)
    {
        delete oknoInformacji;
        oknoInformacji = NULL;
    }

    oknoInformacji = new info(this,"Melduje wykonanie zadania, plik wysłany.",true);
    oknoInformacji->show();

}
