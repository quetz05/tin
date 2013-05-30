#include "message.h"

message::message(/*QObject *parent,*/ QString wiadomosc) //:
    //QObject(parent)
{
    this->wiadomosc = wiadomosc;
}

QString message::Czytaj(int id)
{
    this->przeczytali.insert(id,true);
    return this->wiadomosc;
}
