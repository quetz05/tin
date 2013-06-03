#include "szyfrator.h"
#include <QDebug>
#include <QByteArray>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

Szyfrator::Szyfrator()
{
    basic = new Klucz;
    basic->k[0] = 307707552;
    basic->k[1] = 421327355;
    basic->k[2] = 199322388;
    basic->k[3] = 356690258;

    srand(time(NULL));
}

Szyfrator::~Szyfrator() {
    delete basic;
}


Klucz Szyfrator::wygenerujKlucz()
{
    Klucz nowy;
    nowy.k[0] = rand();
    nowy.k[1] = rand();
    nowy.k[2] = rand();
    nowy.k[3] = rand();

    return nowy;
}

QString Szyfrator::kluczDoStringa(Klucz *k) {

    std::stringstream ss;
    ss << k->k[0] << 'x' << k->k[1] << 'x' << k->k[2] << 'x' << k->k[3];

    return QString(ss.str().c_str());
}

Klucz Szyfrator::stringDoKlucz(QString s) {

    QList<QByteArray> lista = QByteArray(s.toStdString().c_str()).split('x');

    Klucz nowy;
    nowy.k[0] = lista[0].toInt();
    nowy.k[1] = lista[1].toInt();
    nowy.k[2] = lista[2].toInt();
    nowy.k[3] = lista[3].toInt();

    return nowy;
}

void Szyfrator::encrypt(QByteArray *source, QByteArray *dest, Klucz *klucz) {

    if (klucz == NULL)
        klucz = basic;

    int rozmiar = source->length();

    unsigned int v[2];
    int i = 0;

    if (klucz == NULL)
        klucz = basic;

    dest->clear();

    while (1) {
        v[0] = v[1] = 0;

        for (int j = 0; (j < 4) && (i < rozmiar); ++j) {
            v[0] <<= 8;
            v[0] += (*source)[i + j];
        }

        i += 4;

        for (int j = 0; (j < 4) && (i < rozmiar); ++j) {
            v[1] <<= 8;
            v[1] += (*source)[i + j];
        }

        i += 4;

        teaEncrypt(v, klucz);

        dest->append((char*)&v[0], 4);
        dest->append((char*)&v[1], 4);

        if (i >= rozmiar)
            break;
    }
}

void Szyfrator::decrypt(QByteArray *source, QByteArray *dest, Klucz *klucz) {

    if (klucz == NULL)
        klucz = basic;

    int rozmiar = source->length();
    unsigned int v[2];
    int i = 0;
    char *temp;

    unsigned char add[4];

    dest->clear();

    while(1) {

        v[0] = v[1] = 0;
        add[0] = add[1] = add[2] = add[3] = 0;

        for (int j = 0; (j < 4); ++j) {
            add[j] = (*source)[i + j];
        }

        v[0] += add[3];
        v[0] <<= 8;
        v[0] += add[2];
        v[0] <<= 8;
        v[0] += add[1];
        v[0] <<= 8;
        v[0] += add[0];

        i += 4;

        add[0] = add[1] = add[2] = add[3] = 0;

        for (int j = 0; (j < 4); ++j) {
            add[j] = (*source)[i + j];
        }

        v[1] += add[3];
        v[1] <<= 8;
        v[1] += add[2];
        v[1] <<= 8;
        v[1] += add[1];
        v[1] <<= 8;
        v[1] += add[0];

        i += 4;

        teaDecrypt(v, klucz);

        temp = (char*)&v[0];
        for (int j = 3; j >= 0; --j) {
            dest->append(temp[j]);
        }

        if (v[1] != 0) {
            temp = (char*)&v[1];
            for (int j = 3; j >= 0; --j) {
                dest->append(temp[j]);
            }
        }

        if (i >= rozmiar)
            break;
    }
}

void Szyfrator::teaEncrypt(unsigned int *v, Klucz *klucz)
{

    unsigned int v0 = v[0], v1 = v[1];
    unsigned int k[4];
    unsigned int suma = 0, delta = 0x9e3779b9;

    for (int i = 0; i < 4; ++i) {
         k[i] = klucz->k[i];
    }

    for (int i = 0; i < 32; ++i) {
        suma += delta;
        v0 += ( (v1 << 4) + k[0] ) ^ (v1 + suma) ^ ( (v1 >> 5) + k[1]);
        v1 += ( (v0 << 4) + k[2] ) ^ (v0 + suma) ^ ( (v0 >> 5) + k[3]);
    }

    v[0] = v0;
    v[1] = v1;
}

void Szyfrator::teaDecrypt(unsigned int *v, Klucz *klucz)
{
    unsigned int v0 = v[0], v1 = v[1];
    unsigned int k[4];
    unsigned int delta = 0x9e3779b9, suma = delta * 32;

    for (int i = 0; i < 4; ++i) {
        k[i] = klucz->k[i];
    }

    for (int i = 0; i < 32; ++i) {
        v1 -= ( (v0 << 4) + k[2] ) ^ (v0 + suma) ^ ( (v0 >> 5) + k[3] );
        v0 -= ( (v1 << 4) + k[0] ) ^ (v1 + suma) ^ ( (v1 >> 5) + k[1] );
        suma -= delta;
    }

    v[0] = v0;
    v[1] = v1;
}

char* Szyfrator::szyfruj(Wiadomosc *wiad, Klucz *klucz, unsigned int *pSize)
{
    std::stringstream naglowek;
    std::string dane = wiad->trueDane.toStdString();

    naglowek << (int)wiad->naglowek.typ << 'x' << wiad->naglowek.ID << 'x';

    QByteArray prepDane(dane.c_str());
    prepDane = prepDane.toBase64();

    naglowek << prepDane.length();

    //QByteArray wynikowaDane;
    //encrypt(&prepDane, &wynikowaDane, klucz);

    //wynikowaDane = wynikowaDane.toBase64();

    //naglowek << wynikowaDane.size();

    unsigned short size = naglowek.str().size();

    while (size != 25) {
        naglowek << 'x';
        ++size;
    }

    QByteArray prepNaglowek(naglowek.str().c_str());
    prepNaglowek = prepNaglowek.toBase64();

    //QByteArray wynikowaNaglowek;

    //encrypt(&prepNaglowek, &wynikowaNaglowek, klucz);

    //wynikowaNaglowek = wynikowaNaglowek.toBase64();

    unsigned int payloadSize = prepDane.length() + prepNaglowek.length();
    //unsigned int payloadSize = wynikowaDane.length() + wynikowaNaglowek.length();
    *pSize = payloadSize;

    char *wynik = new char[payloadSize];
//    char *temp1 = new char[wynikowaNaglowek.length() + 1];
//    char *temp2 = new char[wynikowaDane.length() + 1];
    memset(wynik, '\0', payloadSize);
//    memset(temp2, '\0', wynikowaDane.length() + 1);
//    memset(temp1, '\0', wynikowaNaglowek.length() + 1);

//    strncpy(temp1, wynikowaNaglowek.data(), wynikowaNaglowek.length());
//    strncpy(temp2, wynikowaDane.data(), wynikowaDane.length());

//    strcat(wynik, temp1);
//    strcat(wynik, temp2);

    strncat(wynik, prepNaglowek.data(), prepNaglowek.length());
    strncat(wynik, prepDane.data(), prepDane.length());

    //strncat(wynik, wynikowaNaglowek.data(), wynikowaNaglowek.length());
    //strncat(wynik, wynikowaDane.data(), wynikowaNaglowek.length());

    //wynikowaDane.clear();
    //wynikowaNaglowek.clear();
    //prepDane.clear();
    //prepNaglowek.clear();

    return wynik;
}

Naglowek Szyfrator::deszyfrujNaglowek(char *data, Klucz *klucz)
{

    QByteArray dane = QByteArray::fromBase64(data);
    //QByteArray wynikowa;

    //decrypt(&dane, &wynikowa, klucz);

    //wynikowa = QByteArray::fromBase64(wynikowa);

    unsigned short ileX = dane.count('x');

    if (ileX > 2)
        dane.chop(ileX - 2);


    QList<QByteArray> wart = dane.split('x');

    char typ;
    unsigned int ID;
    unsigned int size;

    bool a1, a2, a3;

    if (wart.length() != 3) {
        qDebug() << "bad juju - trying different method";

        QString dane(wynikowa.data());

    } else {
        typ = (char)wart[0].toInt(&a1);
        ID = wart[1].toInt(&a2);
        size = wart[2].toInt(&a3);

    }

    ID = ntohs(ID);

    Naglowek naglowek;
    naglowek.typ = typ;
    naglowek.ID = ID;
    naglowek.trueRozmiar = size;

    qDebug() << typ << " :: "<< ID << " :: " << size;

    return naglowek;
}

QString Szyfrator::deszyfrujDane(char *data, Klucz *klucz)
{
    QByteArray dane = QByteArray::fromBase64(data);
    //QByteArray wynikowa;

    //decrypt(&dane, &wynikowa, klucz);

    //wynikowa = QByteArray::fromBase64(wynikowa);

    return QString(dane.data());

}
