#ifndef USERCONECTION_H
#define USERCONECTION_H

#include <QThread>
#include "rozmowa.h"
#include <QMap>
#include <QMutex>
#include "szyfrator.h"
class UserConnection : public QThread
{
    Q_OBJECT
private:
    bool zalogowany;
    int socket;
    int myid;
    Klucz *sekret;
    QMutex mutex; // muteks gwarantujacy nam ze tylko jeden pakiet na raz bedzie wysylany
    // na wszelki wypadek bo sloty wywoluja sie w innym watku


    //trzeba nam jeszcze liste naszych rozmow zeby je jakos obslugiwac
    QMap<int,rozmowa*> rozmowy;
    /**
     * @brief sprzataj przygotowuje nas do wyjscia odlacza od rozmow
     *      czy potrzebne?
     */
    void sprzataj();

    /**
     * @brief rejestruj funkcja rejestrujaca ziomalka
     * @param name nick ziomalka ktorego chcemy zarejestrowac
     * @param pass hash hasla ziomalka :*
     */
    void rejestruj(QString name, QString pass);
    /**
     * @brief loguj funkcja logujaca nas w systemiku
     * @param name nazwa uzytkownika do zalogowania
     * @param pass haslo uzytkownika do zalogowania
     */
    void loguj(QString name, QString pass);
    /**
     * @brief wyslijPakiet wysyla pakiet przez nasz port thread safe
     * @param typ typ pakietu do wyslania
     * @param id lub inna wazna dana
     * @param daneRozm rozmiar danych w ilosci znakow funkcja sama sobie przemnozy
     * @param dane same dane moze byc null wtedy stwierdzamy
     *        ze nie ma danych nawet jak rozmiar bedzie duzy
     */
    void wyslijPakiet(char typ, unsigned int id, QString* dane);

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
     * @param idUsr podaje kto tworzy nową rozmowe
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
