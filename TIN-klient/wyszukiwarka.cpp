#include "wyszukiwarka.h"
#include "ui_wyszukiwarka.h"

wyszukiwarka::wyszukiwarka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wyszukiwarka)
    {
        this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
        ui->setupUi(this);
    }

wyszukiwarka::~wyszukiwarka()
{
    delete ui;
}
