#include "userconnection.h"
#include <unistd.h> // to jest wazny include z opcjami read i write
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include "../wiadomosc.h"

UserConnection::UserConnection(QObject *parent) :
    QThread(parent)
{
    zalogowany = false;
    myid=-1;
}

UserConnection::UserConnection(int socket)
{
    myid=-1;
    this->socket = socket;
    zalogowany = false;
}

///zrobione chyba wszystko
UserConnection::~UserConnection()
{
    for(QMap<int,rozmowa*>::Iterator it=rozmowy.begin();it!=rozmowy.end();++it){
        (it.value())->usunSluchacza(myid);
    }

    close(socket);// zamykamy gniazdo
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
            qDebug()<<"zalogowany urzytkownik\n";
            zalogowany = true;
        }
    }
}
///@todo
void UserConnection::dodanyDoRozmowy(int idUsr, int idRozm,rozmowa *ro,bool czy)
{
    if(idUsr==this->myid){
        rozmowy.insert(idRozm,ro);
    }// czy cos jeszcze??

}

// tu obsługujemy urzytkownika (czytamy jego wypociny)
///@todo
void UserConnection::run()
{
    bool wyjscie=false;
    qDebug() << "wystartowal watek urzytkownika\n";
    while(!wyjscie){ // 0 kod wyjscia
     // tu obróbka danych i wyslanie nowych wiadomosci
        char wiad[4];
        read(socket,wiad,1);
        qDebug()<< wiad[1]<<"\n";
        read(socket,wiad,4);
        qDebug()<< ntohs(*((int*)wiad))<<"\n";
        read(socket,wiad,4);
        qDebug()<< ntohs(*((int*)wiad))<<"\n";
        int rozmiar = *((int*)wiad);
        for(int i=0;i<rozmiar;++i){
            read(socket,wiad,2);
            qDebug() << *((QChar*)wiad);
        }

    }
    emit finished(myid);

}
