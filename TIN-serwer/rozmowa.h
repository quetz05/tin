#ifndef ROZMOWA_H
#define ROZMOWA_H

#include <QObject>
#include <QString>
#include <QVector>
#include "message.h"
#include <QMutex>
/**
 * @brief The rozmowa class
 *obiekt rozmowy zawierajacy kolejke komunikatow i sygnal powiadamiający  wszystkich którzy uczestniczą w rozmowie o nowej wiadomości
 */
class rozmowa : public QObject
{
    Q_OBJECT
    /// liczba urzytkowników uczestniczących w rozmowie
    int userNbr;
    ///wiadomości czekające na odebranie przez co najmniej jednego urzytkownika
    QVector<message> messages;
    /// muteks gwarantujący dostęp przez tylko jeden wontek do struktury
    QMutex mutex;
    int myid;
public:
    /**
     * @brief rozmowa domyslny konstruktor rozmowy
     * @param parent ojciec obiekt
     */
    explicit rozmowa(int id,QObject *parent = 0);
    /**
     * @brief odbiezWiadomosc pozwala uzytkownikowi odebrac pierwsza nieprzeczytana wiadomosc
     *  UWAGA!!! najpierw sprawdz czy takowa istnieje czyWiadomosc()
     * @return napis wiadomosci
     */
    QString odbiezWiadomosc(int);// odbieramy pierwsza nieodczytana wiadomosc
    /**
     * @brief czyWiadomosc sprawdzamy czy czeka jakas wiadomosc dla urzytkownika do odebrania
     * @return czy jest wiadomosc
     */
    bool czyWiadomosc(int);// sprawdzamy czy jest dla nas jakas wiadomosc ktorej jeszcze nie przeczytalismy
    /**
     * @brief wyslijWiadomosc wysyla wiadomosc do obiektu i informuje wszystkich urzytkownikow tej rozmowy ze takowa sie pojawila
     * @param wiadomosc wiadomosc do wyslania
     */
    void wyslijWiadomosc(QString wiadomosc);
    /**
     * @brief dodajSluchacza zwieksza ilosc sluchaczy
     */
    void dodajSluchacza(){mutex.lock();++userNbr;mutex.unlock();}
    /**
     * @brief usunSluchacza usuwa sluchacza z "listy" sluchaczy oraz anuluje jego przeczytanie wiadomosci
     * @param idUsr id sluchacza
     */
    void usunSluchacza(int idUsr);
    /**
     * @brief czySluchacze sprawdza czy jeszcze ktos uczestniczy w tej rozmowie
     * @return czy ktos jeszcze zostal przydaje sie do kasowanie rozmow
     */
    bool czySluchacze(){if(userNbr>0)return true;return false;}
    
signals:
    /**
     * @brief nowaWiadomosc sygnal emitowany gdy pojawi sie nowa wiadomosc
     */
    void nowaWiadomosc(int);

public slots:
    
};

#endif // ROZMOWA_H
