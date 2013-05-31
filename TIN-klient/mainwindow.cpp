#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString login) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    zaznaczonyZnajomy = NULL;
    //wysz = NULL;
    uzytkownik = login;
    bramaZnajomych = new BramaZnajomych(QString(uzytkownik));


    doda = new dodawanie(this,bramaZnajomych);
    oknoWysylania= new QFileDialog(this);

    ui->setupUi(this);


    connect(ui->pushRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijRozmowe()));
    connect(ui->pushWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijWysylanie()));
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


    ui->pushGrupWyslijPlik->setEnabled(false);
    ui->pushGrupRozmawiaj->setEnabled(false);
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

    QString rozmowca = zaznaczonyZnajomy->text();

    if(oknaRozmowy.count(rozmowca)==0)
    {

        oknaRozmowy.insert(rozmowca,new oknoRozmowy(this,uzytkownik,rozmowca));

        connect(oknaRozmowy.value(rozmowca), SIGNAL(koniecRozmowy(const QString &)), this, SLOT(zakonczRozmowe(QString)));

        oknaRozmowy.value(rozmowca)->show();
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
    if(zaznaczonyZnajomy->foreground()==Qt::darkGreen)
    {
        ui->pushRozmawiaj->setEnabled(true);
        ui->pushWyslijPlik->setEnabled(true);
    }
    else
    {
        ui->pushRozmawiaj->setEnabled(false);
        ui->pushWyslijPlik->setEnabled(false);
    }
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

        ui->listaZnajomych->item(0)->setForeground(Qt::darkGreen);
        //ui->listaZnajomych->item(1)->setForeground(Qt::darkGreen);
    }
}

void MainWindow::zakonczDodawanie()
{
    wczytajZnajomych();
    doda->hide();
}

void MainWindow::zakonczRozmowe(const QString &rozmowca)
{
    QMap <QString, oknoRozmowy*>::Iterator it = oknaRozmowy.find(rozmowca);
    delete oknaRozmowy.value(rozmowca);
    oknaRozmowy.erase(it);
}
