#include "szyfrator.h"
#include <QDebug>
#include <QByteArray>

Szyfrator::Szyfrator()
{
}

char* Szyfrator::szyfruj(QString dane, int klucz)
{
    std::string ciag = dane.toStdString();

    QByteArray magia(ciag.c_str());

    magia = magia.toBase64();

    qDebug() << "zaszyfrowano == " << magia.data();

    char *sz = new char[magia.length()];

    strcpy(sz, magia.data());

    return sz;
}

QString Szyfrator::deSzyfruj(const char *dane, int klucz)
{
    QByteArray magia = QByteArray::fromBase64(dane);

    return QString(magia.data());
}
