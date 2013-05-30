#include "userconnection.h"

UserConnection::UserConnection(QObject *parent) :
    QThread(parent)
{
}

void UserConnection::nowaWiadomosc(int id)
{
    // pojawila sie nowa wiadomosc od rozmowy id losowy
    //@todo
}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
void UserConnection::run()
{
}
