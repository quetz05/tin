#include "connection.h"
#include <QDebug>

Connection::Connection(int soc, QObject *parent) :
    QObject(parent)
{

    typInformacji=0;
    gniazdo =soc;

}

int Connection::wyslijPakiet(char *dane, int dlogosc)
{
    // tu nie bedzie tak latwo
}

int Connection::odbiezPakiet(char *bufor, int dlogosc)
{
    memset(bufor,'\0',dlogosc+1);
    int ilePrzeczytano = 0;
    int nowaPartia = 0;
    char *temp;
    temp = new char[dlogosc + 1];
    memset(temp, '\0', dlogosc + 1);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(gniazdo,&readfds);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec= 0;

    while(ilePrzeczytano<dlogosc){
        FD_ZERO(&readfds);
        FD_SET(gniazdo,&readfds);
        int inf = select(this->gniazdo+1,&readfds,NULL,NULL,&tv);
        if(inf>0){
            // mozna odczytywac
            nowaPartia = read(gniazdo,temp,dlogosc - ilePrzeczytano);
            if(nowaPartia<0){
                qDebug() << "Cygan placze nad readem" << this;
                return -1;
            }

            strncat(bufor,temp,nowaPartia);
            ilePrzeczytano += nowaPartia;


        }else{


            if(inf<0){
                qDebug() << "Cygan placze kiedy nie ma gruzu" << this;
                return -1;
            }
            if(this->typInformacji==-1){
                qDebug() << "Odcyganiamy wyjscie";
                return -1;
            }
        }
    }
    delete [] temp;
    return dlogosc;
}

void Connection::wychodzimy()
{
    qDebug() << "Odcyganiamy wyjscie 1.0" << this;
    this->typInformacji = -1;
}

