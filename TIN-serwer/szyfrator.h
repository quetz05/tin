#ifndef SZYFRATOR_H
#define SZYFRATOR_H

#include <QString>
#include "../wiadomosc.h"

#define HEADER_SIZE 56
typedef struct Klucz {

    unsigned int k[4];

} Klucz;

class Szyfrator
{
public:
    Szyfrator();
    ~Szyfrator();

    char* szyfruj(Wiadomosc *wiad, Klucz *klucz, unsigned int *pSize);

    Naglowek deszyfrujNaglowek(char *data, Klucz *klucz);
    QString deszyfrujDane(char* data, Klucz *klucz);

    Klucz wygenerujKlucz();

    QString kluczDoStringa(Klucz *k);
    Klucz stringDoKlucz(QString s);

private:
    Klucz *basic;

    void teaEncrypt(unsigned int *v, Klucz *klucz);
    void teaDecrypt(unsigned int *v, Klucz *klucz);

    void encrypt(QByteArray *source, QByteArray *dest, Klucz *klucz);
    void decrypt(QByteArray *source, QByteArray *dest, Klucz *klucz);
};

#endif // SZYFRATOR_H
