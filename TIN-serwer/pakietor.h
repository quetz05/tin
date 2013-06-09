#ifndef PAKIETOR_H
#define PAKIETOR_H

#include <QObject>
#include"polaczenie.h"
#include <QMutex>
#include "szyfrator.h"
/**
 * @brief The Pakietor class czego chcemy od klasy obudowujacej pakiety ??
 *  1   mozliwosc nadania pakietu o danym naglowku
 *  2   mozliwosc odebrania pakietu o danym naglowku
 */
class Pakietor : public QObject
{
    Q_OBJECT
private:
    QMutex mutek;
    Polaczenie conn;
    int socc;
public:
    explicit Pakietor(int soc, QObject *parent = 0);
    /**
     * @brief odbiezPakiet funkcja odbierajaca pakiety
     * @param naglowek
     * @param id
     * @param wiadomosc
     * @return -1 blad inaczej dlogosc wiadomosci
     */
    int odbiezPakiet(unsigned int* naglowek,unsigned int* id,QString* wiadomosc,Klucz *kluczor);
    /**
     * @brief nadajPakiet funkcja wysylajaca pakiet o danej struktuze
     * @param naglowek typ naglowka
     * @param id pole zawierajace id
     * @param wiadomosc wskaznik na wiadomosc moze byc null jezeli wysylamy sam naglowek
     * @return -1 gdy blad inaczej dlogosc nadanej wiadomosci
     */
    int nadajPakiet(unsigned int naglowek,unsigned int id,QString* wiadomosc,Klucz *kluczor);
signals:
    
public slots:
    void wyjdz();
    
};

#endif // PAKIETOR_H
