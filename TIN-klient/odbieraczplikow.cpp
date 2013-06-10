#include "odbieraczplikow.h"
#include <QFileDialog>
#include <QDebug>

OdbieraczPlikow::OdbieraczPlikow(QString nazwa, QWidget *parent)
{
    plik = new QFile(nazwa);
    plik->open(QIODevice::WriteOnly);
    nazwaPliku = nazwa;

    strumien = new QDataStream(plik);
}

OdbieraczPlikow::~OdbieraczPlikow() {

    plik->close();

    delete plik;
    delete strumien;
}

void OdbieraczPlikow::nowaPartia(QByteArray *partia) {

    QByteArray decode = QByteArray::fromBase64(*partia);

    strumien->writeRawData(decode.data(), decode.length());

    delete partia;

}

void OdbieraczPlikow::zakoncz()
{
    plik->close();

    QFile::remove(nazwaPliku);
}
