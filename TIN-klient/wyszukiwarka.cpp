#include "wyszukiwarka.h"
#include "ui_wyszukiwarka.h"

wyszukiwarka::wyszukiwarka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wyszukiwarka)
{
    ui->setupUi(this);
}

wyszukiwarka::~wyszukiwarka()
{
    delete ui;
}
