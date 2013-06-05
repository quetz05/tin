#include "rozmowa.h"
#include <QDebug>

rozmowa::rozmowa(int id,QObject *parent) :
    QObject(parent)
{
    userNbr = 0;
    myid= id;
    last = "";
}

QString rozmowa::odbiezWiadomosc(int id)
{

    qDebug() << "odbiezWiadomosc( " << id << ");";

    //z powodu zapisu nie mozemy pozwolic na odczytywanie bez mutka
    mutex.lock();
//    qDebug() << "Wielkosc mesage: " << messages.size();
//    qDebug() << "Wielkosc mesage: " << userNbr;

    for(int i=0;i<messages.size();++i){
        if(!messages[i].czyPrzeczytal(id)){
            mutex.unlock();

            qDebug() << "------ sending message for id == " << id;

            QString wiad = "";
            wiad.append(messages[i].Czytaj(id));
            last = "";
            last.append(messages[i].Czytaj(id));

            if(messages[i].iluPrzeczytalo()==userNbr){ //sprawdzamy czy czytamy tą wiadomość jako ostatni jezeli tak to ja usuwamy
                messages.remove(i);
            }
            return wiad;
        }

        /*mutex.unlock();
        QString wiad = "";
        wiad.append(messages[i].Czytaj(id));
        messages.remove(i);*/

        //return wiad;


    }
    mutex.unlock();
    return last;
}
// sprawdzamy czy czeka na nas jakas wiadomosc
bool rozmowa::czyWiadomosc(int id)
{
    for(QVector<message>::Iterator it = messages.begin();it!=messages.end();++it){
        if(it->czyPrzeczytal(id))   return true;
    }
    return false;
}


void rozmowa::wyslijWiadomosc(QString wiadomosc)
{

    // mutek sie przyda bo zapis nie jest atomowy wiec i odczyt musimy bronic
    mutex.lock();

    messages.insert(messages.end(),message(wiadomosc));
    // wstawiamy wiadomosc na koniec a przynajmniej tak nam sie w tej chwili wydaje
    mutex.unlock();
    //po dodaniu nowej wiadomosci informujemy wszystkich ze takowa sie pojawila

    qDebug() << "emitujemy nowa wiadomosc";

    emit nowaWiadomosc(myid);
}

void rozmowa::usunSluchacza(int idUsr)
{
    mutex.lock();
    --userNbr;
    for(int i=0;i<messages.size();++i){
        messages[i].usunInf(idUsr);
        if(messages[i].iluPrzeczytalo() == userNbr){
            messages.remove(i);
        }
    }

    mutex.unlock();

}
