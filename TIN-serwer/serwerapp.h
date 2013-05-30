#ifndef SERWERAPP_H
#define SERWERAPP_H

#include <QObject>
#include<QCoreApplication>
#include <QMap>
#include "userconnection.h"
#include "rozmowa.h"

class SerwerApp : public QObject
{
    Q_OBJECT
private:
    QCoreApplication *app;
    QMap<int,UserConnection*> users;// mapa urzytkowników do przetrzymania
    QMap<int,rozmowa*>   rozmowy;
    int port;
public:
    /**
     * @brief SerwerApp domyslny konstruktor
     * @param parent ojciec obiektu
     */
    explicit SerwerApp(QObject *parent = 0);
    /**
     * @brief quit zluzy do sygnalizacji ze mozna nas zamknac i usunac wszystko co tylko sie da
     */
    void quit();
    
    /**
     * @brief setPort ustawia port z zewnatrz
     * @param value numer portu do nasluchu
     */
    void setPort(int value){port = value;}

signals:
    /**
     * @brief finished sygnal mowiacy ze mozna nas spokojnie zamknac
     */
    void finished();
    /**
     * @brief dodajeDoRozmowy sygnal sluzocy do powiadomienia urzytkownikow ze ktos zostal dodany do rozmowy
     * @param idUsr     urzytkownik dodany do rozmowy
     * @param idRozm rozmowa do ktorej ten zostal dodany
     * @param rozmowa wskaznik na rozmowe do ktorej go dodalismy
     */
    void dodajeDoRozmowy(int idUsr,int idRozm,rozmowa* rozmowa);
    /**
     * @brief dodanoUrzytkownika komunikat o zalogowaniu urzytkownika
     * @param idUsr identyfikator urzytkownika
     * @param status status 1 powodzenie 0 niepowodzenie(ktos juz sie zalogowal na to konto
     */
    void dodanoUrzytkownika(int idUsr,int status);
public slots:
    //nasza funkcyja odpalajaca apke
    void run();

    //nasze powiadomienie ze ktos chce nas zamknac
    void AboutToQuitApp();

    /**
     * @brief dodajDoRozmowy rządanie urzytkownika aby podłączyć kogoś do rozmowy
     * @param idUsr urzytkownik którego chcemy podłączyć 
     * @param idRozm rozmowa do której chcemy podłączyć
     */
    void dodajDoRozmowy(int idUsr,int idRozm);
    /**
     * @brief stworzRozmowe urzytkownik o danym id chce stworzyć rozmowę 
     * @param idUsr id urzytkownika który tworzy rozmowe 
     * @return zwraca id rozmowy 
     *  pytanie czy musi się sam do własnej rozmowy dodać? chyba tak będzie łatwiej 
     */
    void stworzRozmowe(int idUsr);
    /**
     * @brief opuscRozmowe zadanie opuszczenia rozmowy przez urzytkownika
     * @param idUsr identyfikator urzytkownika opuszczajacego rozmowe
     * @param idRozm identyfikator rozmowy opuszczanej
     */
    void opuscRozmowe(int idUsr,int idRozm);
    /**
     * @brief dodajDoMapy zadanie dodania urzytkownika do mapy urzytkownikow nastepuje po dokonaniu miliarda operacji wstepnych (logowania,rejestracji)
     * @param idUsr id urzytkownika 
     */
    void dodajDoMapy(int idUsr, UserConnection *usr);

    void wyszedl(int idUsr);
};

#endif // SERWERAPP_H

