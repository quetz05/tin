#ifndef ODBIERACZPLIKOW_H
#define ODBIERACZPLIKOW_H

#include <QFile>
#include <QDataStream>

class OdbieraczPlikow
{
public:
    OdbieraczPlikow(QString nazwa, QWidget *parent);
    ~OdbieraczPlikow();

    void nowaPartia(QByteArray *partia);

private:
    QFile *plik;
    QDataStream *strumien;

    unsigned int rozmiar;
    unsigned int rozmiar2;
};

#endif // ODBIERACZPLIKOW_H
