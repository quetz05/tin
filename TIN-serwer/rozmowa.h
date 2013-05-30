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
    QVector<message> messages;
    QMutex mutex;
public:
    explicit rozmowa(QObject *parent = 0);
    QString odbiezWiadomosc(int);// odbieramy pierwsza nieodczytana wiadomosc
    bool czyWiadomosc(int);// sprawdzamy czy jest dla nas jakas wiadomosc ktorej jeszcze nie przeczytalismy
    bool wyslijWiadomosc(QString);
    
signals:
    void nowaWiadomosc();
public slots:
    
};

#endif // ROZMOWA_H
