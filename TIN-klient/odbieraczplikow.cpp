#include "odbieraczplikow.h"
#include <QFileDialog>
#include <QDebug>

OdbieraczPlikow::OdbieraczPlikow(QString nazwa, QWidget *parent)
{
    plik = new QFile(nazwa);
    plik->open(QIODevice::WriteOnly);

    strumien = new QDataStream(plik);
    rozmiar = 0;
    rozmiar2 = 0;

}

OdbieraczPlikow::~OdbieraczPlikow() {

    qDebug() << "odebrano << " << rozmiar << " << bajtów";

    plik->close();

    delete plik;
    delete strumien;
}

void OdbieraczPlikow::nowaPartia(QByteArray *partia) {

    qDebug() << "odbieraczDostal == " << (*partia);
    qDebug() << "odbieraczRozmiar == " << partia->length();

    unsigned int ile = strumien->writeRawData(partia->data(), partia->length());

    //if (ile != partia->length())
        qDebug() << "jakieś juju -- ile == " << (unsigned int)ile << " :: length == " << partia->length();

    if (ile == -1)
        qDebug() << "bad juju....";

    rozmiar += ile;

    qDebug() << "odebrano paczek == " << ++rozmiar2;
    //(*strumien) << partia->data();

    delete partia;

}
