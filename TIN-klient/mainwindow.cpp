#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString login, int socket) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    zaznaczonyZnajomy = NULL;
    //wysz = NULL;
    uzytkownik = login;
    bramaZnajomych = NULL;
    gniazdo = socket;
    grRozmowa = NULL;

    el = new ekranLogowania(this,gniazdo);
    el->show();

    //con = new ServerConn();

    connect(el, SIGNAL(logowanie(const QString&)), this, SLOT(zaloguj(QString)));


    doda = NULL;
    oknoWysylania= new QFileDialog(this);

    ui->setupUi(this);


    connect(ui->pushRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijRozmowe()));
    connect(ui->pushWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijWysylanie()));

    connect(ui->pushGrupRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijGrupRozmowe()));
    connect(ui->pushGrupWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijGrupWysylanie()));

    connect(ui->pushSzukajZnajomych, SIGNAL(clicked()), this, SLOT(wyszukiwarkaZnajomych()));

    connect(ui->actionSzukajZnajomych, SIGNAL(triggered()), this, SLOT(wyszukiwarkaZnajomych()));
    connect(ui->actionZakoncz, SIGNAL(triggered()), this, SLOT(zakoncz()));
    connect(ui->actionWyloguj, SIGNAL(triggered()), this, SLOT(wyloguj()));

    connect(ui->pushDodaj, SIGNAL(clicked()), this, SLOT(dodajZnajomego()));
    connect(ui->pushUsun, SIGNAL(clicked()), this, SLOT(usunZnajomego()));
    connect(ui->listaZnajomych, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(zaznaczenieZnajomego(QListWidgetItem *)));

    //wyswietlanie loga
    QGraphicsScene *scene =  new QGraphicsScene();
    QPixmap pixmap(qApp->applicationDirPath() + "/images/tin.jpg");
    scene->addPixmap(pixmap);
    ui->logoView->setScene(scene);
    ui->logoView->show();


    ui->pushRozmawiaj->setEnabled(false);
    ui->pushWyslijPlik->setEnabled(false);
    ui->pushUsun->setEnabled(false);


    ui->pushGrupWyslijPlik->setEnabled(false);
}

MainWindow::~MainWindow()
{

    delete zaznaczonyZnajomy;
    delete doda;
    //delete wysz;
    delete oknoInformacji;
    delete ui;
}


void MainWindow::wyloguj()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::zaloguj(const QString &login)
{

    el->hide();

    uzytkownik = login;

    bramaZnajomych = new BramaZnajomych(QString(uzytkownik));
    doda = new dodawanie(this,bramaZnajomych);

    //wczytywanie listy znajomych
    wczytajZnajomych();

    this->show();
}

void MainWindow::zakoncz()
{
    QApplication::exit();
}

void MainWindow::wyszukiwarkaZnajomych()
{
    //wysz = new wyszukiwarka(this);
    //wysz->show();
}

void MainWindow::rozpocznijRozmowe()
{
    int id = 13;

    QList <QString> rozmowca;
    rozmowca.push_back(zaznaczonyZnajomy->text());

    if(oknaRozmowy.count(id)==0)
    {

        oknaRozmowy.insert(id,new oknoRozmowy(this,id,rozmowca,gniazdo));

        connect(oknaRozmowy.value(id), SIGNAL(koniecRozmowy(int)), this, SLOT(zakonczRozmowe(int)));

        oknaRozmowy.value(id)->show();
    }

}

void MainWindow::rozpocznijWysylanie()
{
    oknoWysylania->show();

}

void MainWindow::dodajZnajomego()
{

    connect(doda, SIGNAL(zakoncz()), this, SLOT(zakonczDodawanie()));

    doda->show();

}

void MainWindow::usunZnajomego()
{
    if(zaznaczonyZnajomy!=NULL)
    {
        int ID = QString(zaznaczonyZnajomy->text()).section("|",1,1).toInt();

        if(!bramaZnajomych->usunZnajomego(ID))
            oknoInformacji = new info(this,"Wystąpił problem przy usuwaniu znajomego. To nie moja wina! Twórcy coś pokopali...",false);
        else
        {
            zaznaczonyZnajomy=NULL;

            wczytajZnajomych();
            ui->pushUsun->setEnabled(false);
            ui->pushRozmawiaj->setEnabled(false);
            ui->pushWyslijPlik->setEnabled(false);
        }
    }
}

void MainWindow::zaznaczenieZnajomego(QListWidgetItem *znajomy)
{
    zaznaczonyZnajomy = znajomy;
    ui->pushUsun->setEnabled(true);

    //dostępność opcji rozmowy/wysłania pliku
  /*  if(zaznaczonyZnajomy->foreground()==Qt::darkGreen)
    {
        ui->pushRozmawiaj->setEnabled(true);
        ui->pushWyslijPlik->setEnabled(true);
    }
    else
    {*/
        ui->pushRozmawiaj->setEnabled(true);
        ui->pushWyslijPlik->setEnabled(true);
    //}
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

        //ui->listaZnajomych->item(0)->setForeground(Qt::darkGreen);
        //ui->listaZnajomych->item(1)->setForeground(Qt::darkGreen);
    }
}

void MainWindow::zakonczDodawanie()
{
    wczytajZnajomych();
    doda->hide();
}

void MainWindow::zakonczRozmowe(int id)
{
    QMap <int, oknoRozmowy*>::Iterator it = oknaRozmowy.find(id);
    delete oknaRozmowy.value(id);
    oknaRozmowy.erase(it);
}

void MainWindow::rozpocznijGrupRozmowe()
{
    if(grRozmowa==NULL)
    {
        znajomi = bramaZnajomych->getListaZnajomych();

        grRozmowa = new GrupowaRozmowa(this, znajomi);

        connect(grRozmowa, SIGNAL(koniec()), this, SLOT(zakonczGrupRoz()));
        connect(grRozmowa, SIGNAL(tworz(const QList<int>&)), this, SLOT(tworzGrupRoz(QList<int>)));
        grRozmowa->show();

    }


}

void MainWindow::zakonczGrupRoz()
{
    delete grRozmowa;
    grRozmowa = NULL;
}


void MainWindow::tworzGrupRoz(const QList<int> &lista)
{
       //wyslij do serwera liste i przyjmij ID rozmowy
    int id = 17;



    QList <QString> rozmowcy;
    for(int i=0; i<lista.length(); i++)
    {
        for(int j=0; j<znajomi.length(); j++)
            if(znajomi[j].second==lista[i])
                rozmowcy.push_back(znajomi[j].first);
    }


    if(oknaRozmowy.count(id)==0)
    {

        oknaRozmowy.insert(id,new oknoRozmowy(this,id,rozmowcy,gniazdo));

        connect(oknaRozmowy.value(id), SIGNAL(koniecRozmowy(int)), this, SLOT(zakonczRozmowe(int)));

        oknaRozmowy.value(id)->show();
    }

}

void MainWindow::rozpocznijGrupWysylanie()
{



}
