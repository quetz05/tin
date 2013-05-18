#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushRozmawiaj, SIGNAL(clicked()), this, SLOT(rozpocznijRozmowe(int*)));
    connect(ui->pushWyslijPlik, SIGNAL(clicked()), this, SLOT(rozpocznijWysylanie(int*)));
    connect(ui->pushSzukajZnajomych, SIGNAL(clicked()), this, SLOT(wyszukiwarkaZnajomych()));

    connect(ui->actionSzukajZnajomych, SIGNAL(triggered()), this, SLOT(wyszukiwarkaZnajomych()));
    connect(ui->actionZakoncz, SIGNAL(triggered()), this, SLOT(zakoncz()));
    connect(ui->actionWyloguj, SIGNAL(triggered()), this, SLOT(wyloguj()));

    //wyswietlanie loga
    QGraphicsScene *scene =  new QGraphicsScene();
    QPixmap pixmap(qApp->applicationDirPath() + "/images/tin.jpg");
    scene->addPixmap(pixmap);
    ui->logoView->setScene(scene);
    ui->logoView->show();





    ui->pushRozmawiaj->setEnabled(false);
    ui->pushWyslijPlik->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::wyloguj()
{




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
