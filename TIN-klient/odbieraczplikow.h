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
    void zakoncz();

private:
    QFile *plik;
    QDataStream *strumien;
    QString nazwaPliku;
};

#endif // ODBIERACZPLIKOW_H
