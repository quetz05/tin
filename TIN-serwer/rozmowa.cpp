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
            QString wiad =messages[i].Czytaj(id);
            if(messages[i].iluPrzeczytalo()==userNbr){ //sprawdzamy czy czytamy tą wiadomość jako ostatni jezeli tak to ja usuwamy
                messages.remove(i);
            }
            return wiad;
        }
    }
    mutex.unlock();
    return QString("0");
}


void rozmowa::wyslijWiadomosc(QString wiadomosc)
{
    // mutek sie przyda bo zapis nie jest atomowy wiec i odczyt musimy bronic
    mutex.lock();

    messages.insert(messages.end(),message(wiadomosc));// wstawiamy wiadomosc na koniec a przynajmniej tak nam sie w tej chwili wydaje
    mutex.unlock();
    //po dodaniu nowej wiadomosci informujemy wszystkich ze takowa sie pojawila
    emit nowaWiadomosc();
}

void rozmowa::usunSluchacza(int idUsr)
{
    mutex.lock();
    --userNbr;
    for(int i=0;i<messages.size();++i){
        messages[i].usunInf(idUsr);
        if(messages[i].iluPrzeczytalo()==userNbr){
            messages.remove(i);
        }
    }

    mutex.unlock();
}
