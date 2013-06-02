#include "szyfrator.h"
#include <QDebug>
#include <QByteArray>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

Szyfrator::Szyfrator()
{
}

   //typ, ID, rozmiar, dane

char* Szyfrator::szyfruj(Wiadomosc *wiad, int klucz, unsigned int *pSize)
{
    //qDebug() << "--- szyfrowanie start ---";

    std::stringstream naglowek;
    std::string dane = wiad->trueDane.toStdString();

    naglowek << (int)wiad->naglowek.typ << 'x' << wiad->naglowek.ID << 'x';

    QByteArray prepDane(dane.c_str());
    prepDane = prepDane.toBase64();

    //qDebug() << "data encoded";

    naglowek << (prepDane.size() + 1);

    unsigned short size = naglowek.str().size();

    while (size != 25) {
        naglowek << 'x';
        ++size;
    }

    QByteArray prepNaglowek(naglowek.str().c_str());
    prepNaglowek = prepNaglowek.toBase64();

    //qDebug() << "header encoded";

    unsigned int payloadSize = prepNaglowek.length() + prepDane.length() + 1;
    *pSize = payloadSize;

    //qDebug() << prepNaglowek.length() << " :: " << prepDane.length();
    //qDebug() << "paylodSize == " << payloadSize;

    char *wynik = new char[payloadSize];
    memset(wynik, '\0', payloadSize);

    strcat(wynik, prepNaglowek.data());
    strcat(wynik, prepDane.data());

    //qDebug() << "payload == " << wynik;

    //qDebug() << "--- szyfrowanie stop ---";
    return wynik;
}

Naglowek Szyfrator::deszyfrujNaglowek(char *data, int klucz)
{
    //qDebug() << "--- naglowek deszyfr ---";

    QByteArray dane = QByteArray::fromBase64(data);

    unsigned short ileX = dane.count('x');

    if (ileX > 2)
        dane.chop(ileX - 2);


    QList<QByteArray> wart = dane.split('x');

    bool a1, a2, a3;

    char typ = (char)wart[0].toInt(&a1);
    unsigned int ID = wart[1].toInt(&a2);
    unsigned int size = wart[2].toInt(&a3);

    ID = ntohs(ID);

    Naglowek naglowek;
    naglowek.typ = typ;
    naglowek.ID = ID;
    naglowek.trueRozmiar = size;

    //qDebug() << "got == " << naglowek.typ << " :: " << naglowek.ID << " :: " << naglowek.trueRozmiar;
    //qDebug() << "--- deszyfrowanie nagl stop ---";

    return naglowek;
}

QString Szyfrator::deszyfrujDane(char *data, int klucz)
{
    //qDebug() << "--- deszyfruj dane ---";


    QByteArray dane = QByteArray::fromBase64(data);

    //qDebug() << dane;
    //qDebug() << dane.data();

    QString x(dane.data());

    //qDebug() << x;
    //qDebug() << "--- deszyfruj dane stop ---";

    return QString(dane.data());

}

char* Szyfrator::szyfruj(QString dane, int klucz)
{
    std::string ciag = dane.toStdString();

    QByteArray magia(ciag.c_str());

    magia = magia.toBase64();

    //qDebug() << "zaszyfrowano == " << magia.data();
    //qDebug() << "zaszyfrowano dlug == " << magia.length();

    char *sz = new char[magia.length()];

    strcpy(sz, magia.data());

    ////qDebug() << "sz dlugosc == " << strlen(sz);

    return sz;
}

QString Szyfrator::deSzyfruj(char *dane, int klucz)
{
    QByteArray magia = QByteArray::fromBase64(dane);

    return QString(magia.data());
}
