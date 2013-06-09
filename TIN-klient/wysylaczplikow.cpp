#include "wysylaczplikow.h"
#include <QDebug>

WysylaczPlikow::WysylaczPlikow(QFile *co, int socket, int doKogo, QObject *parent) : QObject(parent)
{
    src = co;
    gniazdo = socket;
    idCelu = doKogo;

}

WysylaczPlikow::~WysylaczPlikow() {

    delete src;
}

void WysylaczPlikow::run() {

    unsigned int counter = 0;
    unsigned int rozmiar = src->size();
    unsigned int ilePoszlo = 0;
    unsigned int dataSize = 0;
    char *temp = new char[257];
    memset(temp, '\0', 257);
    char *send;
    unsigned int aktSize = 0;

    Szyfrator szyfr;
    Wiadomosc *wiad;
    QDataStream wejscie(src);

    while (ilePoszlo < rozmiar) {

        aktSize = wejscie.readRawData(temp, 256);

        if (aktSize == -1)
            break;

        qDebug() << "przeczytano bajtow == " << aktSize;
        qDebug() << "przeczytano << " << temp;

        wiad = new Wiadomosc(PLIK_TRANSFER, idCelu, QString(""), gniazdo);
        send = szyfr.szyfrujPlik(wiad, NULL, &dataSize, temp, aktSize);

        qDebug() << "wyslano == " << send;

        wiad->wyslijDoSerwera(send, dataSize);
        ilePoszlo += aktSize;

        qDebug() << "poszlo ==== " << ++counter;

        delete send;
        delete wiad;
        memset(temp, '\0', 257);
    }

    delete temp;

    wiad = new Wiadomosc(PLIK_KONIEC, idCelu, QString(""), gniazdo);
    send = szyfr.szyfruj(wiad, NULL, &dataSize);
    wiad->wyslijDoSerwera(send, dataSize);

    delete send;
    delete wiad;


    qDebug() << "zakonczylem wysyl pliki";
    qDebug() << "wysylacz :: rozmiar == " << rozmiar;
    qDebug() << "wysylacz :: ilePosz == " << ilePoszlo;
}
