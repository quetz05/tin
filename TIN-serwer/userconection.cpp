#include "userconnection.h"

UserConnection::UserConnection(QObject *parent) :
    QThread(parent)
{
    zalogowany = false;
}

UserConnection::UserConnection(int socket)
{
    this->socket = socket;
    zalogowany = false;
}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{
    for(QMap<rozmowa*>::Iterator it=rozmowy.begin();it!=rozmowy.end();++it){
        (it.value())->usunSluchacza(myid);
    }

}

void UserConnection::nowaWiadomosc(int id)
{
    // pojawila sie nowa wiadomosc od rozmowy id losowy to wypychamy ja na gniazd
    ///@todo
}
///@todo
void UserConnection::pojawilSieUsr(int idUsr, int status)
{
    if(!zalogowany && idUsr==myid){
        if(status){
            Qdebug()<<"zalogowany urzytkownik\n";
            zalogowany = true;
        }
    }
}
///@todo
void UserConnection::dodanyDoRozmowy(int idUsr, int idRozm,rozmowa *ro)
{
    if(idUsr==this->myid){
        rozmowy.insert(idRozm,ro);
    }// czy cos jeszcze??

}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
///@todo
void UserConnection::run()
{
}
