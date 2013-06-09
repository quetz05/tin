#include "wysylaczplikow.h"
#include <QDebug>

WysylaczPlikow::WysylaczPlikow(QFile *co, int socket, int doKogo, QObject *parent) : QObject(parent)
{
    src = co;
    gniazdo = socket;
    idCelu = doKogo;
    anuluj = false;

}

WysylaczPlikow::~WysylaczPlikow() {

    delete src;
}

void WysylaczPlikow::timeout()
{
    mutex.lock();
    anuluj = true;
    mutex.unlock();

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
    QByteArray qba;


    while (ilePoszlo < rozmiar) {

        mutex.lock();

        if (anuluj)
            break;

        aktSize = wejscie.readRawData(temp, 256);

        if (aktSize == -1)
            break;

        qba = QByteArray::fromRawData(temp, aktSize);
        qba = qba.toBase64();

        wiad = new Wiadomosc(PLIK_TRANSFER, idCelu, QString(qba.data()), gniazdo);
        send = szyfr.szyfruj(wiad, NULL, &dataSize);

        wiad->wyslijDoSerwera(send, dataSize);
        ilePoszlo += aktSize;

        delete send;
        delete wiad;
        memset(temp, '\0', 257);

        mutex.unlock();
    }

    delete temp;

    if (!anuluj) {
        wiad = new Wiadomosc(PLIK_KONIEC, idCelu, QString(""), gniazdo);
        send = szyfr.szyfruj(wiad, NULL, &dataSize);
        wiad->wyslijDoSerwera(send, dataSize);

        delete send;
        delete wiad;

        emit koniec();
    }

}
