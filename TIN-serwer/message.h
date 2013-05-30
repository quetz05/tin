#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QMap>
/**
 * @brief The message class
 *  klasa przechowująca wiadomość oraz dane kto ją przeczytał
 */
class message //: public QObject
{
   // Q_OBJECT
private:

    QMap<int,bool> przeczytali;
    QString wiadomosc;
public:

    explicit message(QString wiadomosc= "0");
    bool czyPrzeczytal(int k){return przeczytali.contains(k);  }//sprawdzamy czy dany koles przeczytal nasza wiadomosc
    QString Czytaj(int id); //odczytujemy wiadomość ze wskazaniem na to
    
//signals:
    
//public slots:
    
};

#endif // MESSAGE_H
