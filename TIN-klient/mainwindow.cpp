#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString login) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    zaznaczonyZnajomy = NULL;
    wysz = NULL;
    doda=NULL;
    bramaZnajomych = new BramaZnajomych(QString(login));



    ui->setupUi(this);

    //connect(ui->pushRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijRozmowe(int*)));
    //connect(ui->pushWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijWysylanie(int*)));
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

    //wczytywanie listy znajomych
    wczytajZnajomych();

    ui->pushRozmawiaj->setEnabled(false);
    ui->pushWyslijPlik->setEnabled(false);
    ui->pushUsun->setEnabled(false);
}

MainWindow::~MainWindow()
{

    delete zaznaczonyZnajomy;
    delete doda;
    delete wysz;
    delete oknoInformacji;
    delete ui;
}


void MainWindow::wyloguj()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void MainWindow::zakoncz()
{
    QApplication::exit();
}

void MainWindow::wyszukiwarkaZnajomych()
{
    wysz = new wyszukiwarka(this);
    wysz->show();
}

void MainWindow::rozpocznijRozmowe(int *listaUczestnikow)
{




}

void MainWindow::rozpocznijWysylanie(int *listaUczestnikow)
{



}

void MainWindow::dodajZnajomego()
{
    doda = new dodawanie(this,bramaZnajomych);
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
            ui->listaZnajomych->clear();

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
    ui->pushRozmawiaj->setEnabled(true);
    ui->pushWyslijPlik->setEnabled(true);
}

void MainWindow::wczytajZnajomych()
{
    znajomi = bramaZnajomych->getListaZnajomych();

    for(int i = 0; i<znajomi.length(); i++)
    {
        ui->listaZnajomych->addItem(znajomi[i].first +"  "+"|"+QString::number(znajomi[i].second)+"|");
    }
}
