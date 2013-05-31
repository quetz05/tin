#ifndef USERCONECTION_H
#define USERCONECTION_H

#include <QThread>
#include "rozmowa.h"
#include <QMap>

class UserConnection : public QThread
{
    Q_OBJECT
private:
    bool zalogowany;
    int socket;
    int myid;
    //trzeba nam jeszcze liste naszych rozmow zeby je jakos obslugiwac
    QMap<int,rozmowa*> rozmowy;
    /**
     * @brief odbiezNaglowek funkcja wczytuje naglowek i go dekoduje
     * @param dataSize wielkosc danych ktore sa przekazane w wiadomosci
     * @return zwraca kod naglowka
     */
    int odbiezNaglowek(int* dataSize);


protected:
    /**
     * @brief run petla glowna programu
     */
    void run();
public:
    /**
     * @brief UserConnection domyslny konstruktor
     * @param parent obiekt ktory jest ojcem naszego
     */
    explicit UserConnection(QObject *parent = 0);
    /**
     * @brief UserConnection konstruktor ktory tworzy polaczenie na podstawie gniazda
     * @param socket deskryptor gniazda przekazywany do watku urzytkownika
     */
    UserConnection(int socket);
    /**
     * Destruktor domyslny
     **/
    ~UserConnection();
    
signals:
    /**
     * @brief dodajRozmowce sygnał który dodaje nowego rozmówcę do naszej rozmowy
     * @param idUsr id nowego rozmowcy
     * @param idRozm id rozmowy
     */
    void dodajeRozmowce(int idUsr,int idRozm);
    /**
     * @brief tworzRozmowe wysyła rządanie stworzenia nowej rozmowy
     * @param idUsr podaje kto tworzy nową rozmowe nie wiem czy potrzebne @?
     * @return zwraca id nowej rozmowy
     */
    void tworzeRozmowe(int idUsr);
    /**
     * @brief opuszczamRozmowe zadanie opuszczenia rozmowy
     * @param idUsr id nasze jak opuszczamy rozmowe
     * @param idRozm id rozmowy ktora oopuszczamy
     */
    void opuszczamRozmowe(int idUsr,int idRozm);
    /**
     * @brief dodajeSieDoListy sygnal zglaszajocy chec dodania sie do listy uzytkownikow z danym id( wywolujemy po zalogowaniu sie/ zarejestrowaniu
     * @param idUsr id urzytkownika jako ktory chcemy sie dodac do listy
     * @return zwraca sukces lub porazke operacji porazka oznacza ze juz taki ktos jest
     */
    void dodajeSieDoListy(int idUsr,UserConnection* usr);
    /**
     * @brief finished wychodzimy
     */
    void finished(int idUsr);
public slots:
    /**
     * @brief dodanyDoRozmowy slocik ktory informuje nas ze dodano nas do rozmowy i przekazuje nam id rozmowy
     * @param idRozm take cos z takim czyms
     */
    void dodanyDoRozmowy(int idUsr, int idRozm, rozmowa* ro, bool czy);

    /**
     * @brief nowaWiadomosc powiadomienie o przyjsciu nowej wiadomosci
     * @param id rozmowy ktora powiadamia nas o zajsciuool
     */
    void nowaWiadomosc(int id);
    /**
     * @brief pojawilSieUsr informacja ze sie logujemy
     * @param idUsr id Usera co to sie logowal
     * @param status czy gosciowi udalo sie w nas wejsc
     */
    void pojawilSieUsr(int idUsr,int status);
};

#endif // USERCONECTION_H
