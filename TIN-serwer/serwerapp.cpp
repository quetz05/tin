#include "serwerapp.h"
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#define PULA 128
// pula jeszce nie odebranych połączeń na sockecie

// konstruktor defoultowy
SerwerApp::SerwerApp(QObject *parent) :
    QObject(parent)
{
    // pobieramy instancje aplikacji glownej jeszcze nie wiem po co ale narazie tak jest w tutku
    app = QCoreApplication::instance();


}
//funkcja zamykajaca program
void SerwerApp::quit()
{
    // po sprzatnieciu sygnalizujemy ze mozna nas zamknac
    emit finished();
}


//funkcja zawierajaca petle programu
void SerwerApp::run()
{
    int sockfd;
    // otwieramy nowe gniazdo
    if((sockfd =socket(AF_INET,SOCK_STREAM,0))<0){// Robimy ideanalnie jak w przykładnie
        qDebug()<< "error nie udalo sie otworzyc gniazd\n";
        quit();
        return;
    }
    struct sockaddr_in sadr;// strukturka adresu dla funkcji bind jeszcze nie wiem jak to działa
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

    //nakurwiamy petle uruchamiajaca miliard watkow urzytkownikow
    while(1){
        struct sockaddr_in cliaddr;
        unsigned int addrlen=sizeof(cliaddr);
        int sock2=accept(sockfd,(struct sockaddr*)&cliaddr,&addrlen);
        // jak się ktoś podłączy to tu go startujemy jupi


    }
    qDebug() << "apka sie odpaliła\n";
    //na koncu wychodzimy z apki
    quit();
}
// slot informujacy nas o zamykaniu zatrzymujemy watki i czyscimy po sobie
void SerwerApp::AboutToQuitApp()
{
}
