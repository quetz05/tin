#include "rozmowa.h"

rozmowa::rozmowa(QObject *parent) :
    QObject(parent)
{
}

QString rozmowa::odbiezWiadomosc(int id)
{

    //z powodu zapisu nie mozemy pozwolic na odczytywanie bez mutka
    mutex.lock();
    for(int i=0;i<messages.size();++i){
        if(!messages[i].czyPrzeczytal(id)){
            mutex.unlock();
            return messages[i].Czytaj(id);
        }

    }
    mutex.unlock();
    return QString("0");
}


bool rozmowa::wyslijWiadomosc(QString wiadomosc)
{
    // mutek sie przyda bo zapis nie jest atomowy wiec i odczyt musimy bronic
    mutex.lock();
    QVector<message>::Iterator iter = this->messages.insert(messages.end(),wiadomosc);// wstawiamy wiadomosc na koniec a przynajmniej tak nam sie w tej chwili wydaje
    mutex.unlock();
    //po dodaniu nowej wiadomosci informujemy wszystkich ze takowa sie pojawila
    emit nowaWiadomosc();
}
