#ifndef SZYFRATOR_H
#define SZYFRATOR_H

#include <QString>
#include "../wiadomosc.h"

#define HEADER_SIZE 56

/**
 * @brief Struktura klucza
 * Struktura zawierająca 4 wartości typu unsigned integer, tworzące klucz 128 bitowy
 *
 */
typedef struct Klucz {

    unsigned int k[4];

} Klucz;

/**
 * @brief Klasa Szyfrator
 * Klasa odpowiedzialna za kodowanie i odkodowywanie danych, oraz generację kluczy.
 */
class Szyfrator {

public:
    /**
     * @brief Szyfrator
     * Konstruktor klasy.
     */
    Szyfrator();
    ~Szyfrator();

    /**
     * @brief szyfruj
     * Metoda odpowiedzialna za zaszyfrowanie wiadomości.
     * @param wiad
     * Wskaźnik na wiadomość do zaszyfrowania.
     * @param klucz
     * Wskaźnik na klucz który ma zostać użyty do zaszyfrowania.
     * @param pSize
     * Wskaźnik na zmienną, do której zostanie wpisany końcowy rozmiar wiadomości do przesłania.
     * @return
     * Zwracana jest tablica bajtów, będących zaszyfrowaną reprezentacją wiadomości.
     */
    char* szyfruj(Wiadomosc *wiad, Klucz *klucz, unsigned int *pSize);

    /**
     * @brief deszyfrujNaglowek
     * Metoda odpowiedzialna za odszyfrowanie nagłówka.
     * @param data
     * Ciag bajtów do odszyfrowania.
     * @param klucz
     * Klucz którym należy odszyfrować dane.
     * @return
     * Zwracana jest struktura Nagłówka.
     */
    Naglowek deszyfrujNaglowek(char *data, Klucz *klucz);

    /**
     * @brief deszyfrujDane
     * Metoda odpowiedzialna za odszyfrowanie danych.
     * @param data
     * Ciąg bajtów do odszyfrowania.
     * @param klucz
     * Klucz którym należy odszyfrować dane.
     * @return
     * Zwracany jest QString zawierający przesłane dane.
     */
    QString deszyfrujDane(char* data, Klucz *klucz);

    /**
     * @brief wygenerujKlucz
     * Metoda generuje nowy klucz.
     * @return
     * Zwracana jest struktura klucza z przypisaną wartością.
     */
    Klucz wygenerujKlucz();

    /**
     * @brief kluczDoStringa
     * Metoda tworzy znakową reprezentację klucza.
     * @param k
     * Wskaźnik na klucz którego reprezentacja będzie tworzona.
     * @return
     * Zwracany jest QString będący znakową reprezentacją klucza.
     * Poszczególne wartości oddzielone są znakiem 'x'.
     */
    QString kluczDoStringa(Klucz *k);
    /**
     * @brief stringDoKlucz
     * Metoda tworzy klucz z jego znakowej reprezentacji.
     * @param s
     * QString będący reprezentacją klucza.
     * @return
     * Klucz utworzony z jego znakowej reprezentacji.
     */
    Klucz stringDoKlucz(QString s);

private:
    /**
     * @brief teaEncrypt
     * Metoda szyfrująca blok (64 bity) zadanym kluczem.
     * @param v
     * Blok danych do zaszyfrowania. Wynik zwracany jest w tym parametrze.
     * @param klucz
     * Klucz którym dane będą szyfrowane.
     */
    void teaEncrypt(unsigned int *v, Klucz *klucz);

    /**
     * @brief teaDecrypt
     * Metoda deszyfrująca blok (64 bity) zadanym kluczem.
     * @param v
     * Blok danych do odszyfrowania. Wynik zwracany jest w tym parametrze.
     * @param klucz
     * Klucz którym dane będa odszyfrowane.
     */
    void teaDecrypt(unsigned int *v, Klucz *klucz);

    /**
     * @brief encrypt
     * Metoda szyfrująca zadany ciąg bajtów.
     * @param source
     * Źródłowy ciąg bajtów do zaszyfrowania.
     * @param dest
     * Obiekt do którego zostanie zapisany zaszyfrowany ciąg. Obiekt jest czyszczony na początku metody.
     * @param klucz
     * Klucz według którego nastąpi szyfrowanie.
     */
    void encrypt(QByteArray *source, QByteArray *dest, Klucz *klucz);

    /**
     * @brief decrypt
     * Metoda odszyfrowująca zadany ciąg bajtów.
     * @param source
     * Źródłowy ciąg bajtów do odszyfrowania.
     * @param dest
     * Obiekt do którego zostanie zapisany odszyfrowany ciąg. Obiekt jest czyszczony na początku metody.
     * @param klucz
     * Klucz według którego dane będą odszyfrowywane.
     */
    void decrypt(QByteArray *source, QByteArray *dest, Klucz *klucz);

    /**
     * @brief basic
     * Klucz "standardowy", wykorzystywany gdy nie podany zostanie inny klucz.
     */
    Klucz *basic;
};

#endif // SZYFRATOR_H
