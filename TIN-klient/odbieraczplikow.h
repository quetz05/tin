#ifndef ODBIERACZPLIKOW_H
#define ODBIERACZPLIKOW_H

#include <QFile>
#include <QDataStream>

class OdbieraczPlikow
{
public:
    OdbieraczPlikow(QString nazwa, QWidget *parent);
    ~OdbieraczPlikow();

    unsigned int ustawIlosc(unsigned int ile) { ilePaczek = ile; }
    unsigned int dajPostep() { return (postep * 100) / ilePaczek; }
    void nowaPartia(QByteArray *partia);
    void zakoncz();

private:
    QFile *plik;
    QDataStream *strumien;
    QString nazwaPliku;
    unsigned int postep;
    unsigned int ilePaczek;
};

#endif // ODBIERACZPLIKOW_H
