#include "serwerapp.h"
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include "userconnection.h"
#include <unistd.h>
#include <QThreadPool>

#define PULA 128
// pula jeszce nie odebranych połączeń na sockecie

// konstruktor defoultowy
SerwerApp::SerwerApp(QObject *parent) :
    QObject(parent)
{
    // pobieramy instancje aplikacji glownej jeszcze nie wiem po co ale narazie tak jest w tutku
    app = QCoreApplication::instance();
    wychodzimy = false;

}
//funkcja zamykajaca program
void SerwerApp::quit()
{
    close(this->sockett);
    // po sprzatnieciu sygnalizujemy ze mozna nas zamknac
    emit finished();
}


//funkcja zawierajaca petle programu
void SerwerApp::run()
{
    QThreadPool::globalInstance()->setMaxThreadCount(PULA);
    int sockfd;
    // otwieramy nowe gniazdo

    if((sockfd =socket(AF_INET,SOCK_STREAM,0))<0){// Robimy ideanalnie jak w przykładnie
        qDebug()<< "error nie udalo sie otworzyc gniazd\n";
        quit();
        return;
    }
    struct sockaddr_in sadr;// strukturka adresu dla funkcji bind
    sadr.sin_family= AF_INET;
    sadr.sin_addr.s_addr = INADDR_ANY;
    sadr.sin_port = htons(port);

    if(bind(sockfd,(struct sockaddr*)&sadr,sizeof(sadr))!=0){
        qDebug()<< "error nie udalo się zarejestrować serwera\n";
        quit();
        return;
    }
    if(listen(sockfd,PULA)!=0){
        qDebug()<< "error nie udalo się przejść w tryb nasłuchu\n";
        quit();
        return;
    }
    sockett = sockfd;
     qDebug() << "start serwera (rozpoczecie nasłuchu)\n";
    //nakurwiamy petle uruchamiajaca miliard watkow urzytkownikow
    while(!wychodzimy){
        struct sockaddr_in cliaddr;
        unsigned int addrlen=sizeof(cliaddr);
        int sock2=accept(sockfd,(struct sockaddr*)&cliaddr,&addrlen);
        if (sock2>0){
            UserConnection *con= new UserConnection(sock2);
            // uzytkownik moze dodac rozmowce
            //watki.push_back(con);
            // sprawdzić różne typy connect'ów
            // w szczególności QBlockedConnection

            qDebug() << "connection pointer == " << con;
            bool status;
            status = connect(con,SIGNAL(dodajeRozmowce(int ,int )),this,SLOT(dodajDoRozmowy(int ,int )), Qt::DirectConnection);
            qDebug() << status;
            // uzytkownik moze stworzyc rozmowe
            status = connect(con,SIGNAL(tworzeRozmowe(int )),this,SLOT(stworzRozmowe(int )), Qt::DirectConnection);
            // uzytkownik moze opuscic rozmowe
            status = connect(con,SIGNAL(opuszczamRozmowe(int  ,int )),this,SLOT(opuscRozmowe(int ,int )), Qt::DirectConnection);
            qDebug() << status;
            // uzytkownik moze dodac sie do zalogowanych jak juz sie zaloguje
            status = connect(con,SIGNAL(dodajeSieDoListy(int,UserConnection*)),this,SLOT(dodajDoMapy(int,UserConnection*)), Qt::DirectConnection);
            qDebug() << status;
            // uzytkownik moze zostac dodany do rozmowy
            status = connect(this,SIGNAL(dodajeDoRozmowy(int,int,rozmowa*,bool)),con,SLOT(dodanyDoRozmowy(int,int,rozmowa*,bool)), Qt::DirectConnection);
            qDebug() << status;
            //rozglaszamy ze ktos sie pojawil i czy mu sie udalo
            status = connect(this,SIGNAL(dodanoUrzytkownika(int,int)),con,SLOT(pojawilSieUsr(int,int)), Qt::DirectConnection);
            qDebug() << status;
            // uzytkownik zglasza ze wychodzi
            status = connect(this,SIGNAL(killEmAll()),con,SLOT(zabij()), Qt::DirectConnection);
            qDebug() << status;
            status = connect(con,SIGNAL(giveUsr(bool*,int,UserConnection**)),this,SLOT(zwrocUzytkownika(bool*,int,UserConnection**)));
            qDebug() << status;
            QThreadPool::globalInstance()->start(con);
        }
    }

    //na koncu wychodzimy z apki
    quit();
}
// slot informujacy nas o zamykaniu zatrzymujemy watki i czyscimy po sobie
void SerwerApp::AboutToQuitApp()
{
    emit killEmAll();

    qDebug()<<"zabijamy";
    wychodzimy=true;
    quit();
}
///zrobione
void SerwerApp::dodajDoRozmowy(int idUsr, int idRozm)
{
    if(rozmowy.contains(idRozm)){
        rozmowy[idRozm]->dodajSluchacza();
        emit dodajeDoRozmowy(idUsr,idRozm,rozmowy[idRozm],0);

    }
}
///zrobione
void SerwerApp::stworzRozmowe(int idUsr)
{
    qDebug() << "tworze rozmowe";
    int i =1;
    while(rozmowy.contains(i)) { ++i; }
    rozmowy.insert(i,new rozmowa(i));
    rozmowy[i]->dodajSluchacza();

    emit dodajeDoRozmowy(idUsr,i,rozmowy[i],1);
}
///zrobione
void SerwerApp::opuscRozmowe(int idUsr, int idRozm)
{
    if(rozmowy.contains(idRozm)){
            rozmowy[idRozm]->usunSluchacza(idUsr);

        if(!(rozmowy[idRozm]->czySluchacze())) {
            delete rozmowy[idRozm];
            rozmowy.remove(idRozm);

        }

    }
}
///zorbione
void SerwerApp::dodajDoMapy(int idUsr,UserConnection* usr)
{
    if(!users.contains(idUsr)){
        users.insert(idUsr,usr);
        emit dodanoUrzytkownika(idUsr,1);//ok
    }
    emit dodanoUrzytkownika(idUsr,0);// blad
}

void SerwerApp::zwrocUzytkownika(bool* czyjest,int id,UserConnection ** usr)
{
    // zwracamy wsk na usr
    if(users.contains(id)){
        (*usr)=users[id];
        (*czyjest)=true;
        return;
    }
    (*czyjest)=false;
}
///zrobione
/*
void SerwerApp::wyszedl()
{//usuwamy urzytkownika jego destruktor powinien nam zrobic przysluge zamknac polaczenie
    UserConnection* Usr = static_cast<UserConnection*>(QObject::sender());

    int i =watki.indexOf(Usr);
    delete Usr;
    watki.remove(i);
    //delete users[idUsr];
    //users.remove(idUsr);
}*/
