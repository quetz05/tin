#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent, QString info, bool ok) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);

    connect(ui->pushOK, SIGNAL(clicked()), this, SLOT(zakoncz()));
    ui->informacja->setPlainText(info);
    ui->informacja->setReadOnly(true);

    if(ok)
    {
        QGraphicsScene *scene =  new QGraphicsScene();
        QPixmap pixmap(qApp->applicationDirPath() + "/images/ok.jpg");
        scene->addPixmap(pixmap);
        ui->picture->setScene(scene);
        ui->picture->show();

    }
    else
    {
        QGraphicsScene *scene =  new QGraphicsScene();
        QPixmap pixmap(qApp->applicationDirPath() + "/images/error.jpg");
        scene->addPixmap(pixmap);
        ui->picture->setScene(scene);
        ui->picture->show();

    }


    this->show();


}

info::~info()
{
    delete ui;
}

void info::zakoncz()
{
    this->~info();
}
