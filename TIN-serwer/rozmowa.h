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
public:
    explicit rozmowa(QObject *parent = 0);
    QString odbiezWiadomosc(int);// odbieramy pierwsza nieodczytana wiadomosc
    bool czyWiadomosc(int);// sprawdzamy czy jest dla nas jakas wiadomosc ktorej jeszcze nie przeczytalismy
    void wyslijWiadomosc(QString);
    void dodajSluchacza(){mutex.lock();++userNbr;mutex.unlock();}
    void usunSluchacza(int idUsr);
    bool czySluchacze(){if(userNbr>0)return true;return false;}
    
signals:
    void nowaWiadomosc();
public slots:
    
};

#endif // ROZMOWA_H
