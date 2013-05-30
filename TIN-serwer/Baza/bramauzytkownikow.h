#ifndef BRAMAUZYTKOWNIKOW_H
#define BRAMAUZYTKOWNIKOW_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>

/**
 * error zwracany w przypadku gdy proba polaczania z baza sie nie uda
 */
#define ER_OPEN_DB -10

/**
 * error zwracany w przypadku gdy nie uda sie wykonac polecenia sql
 */
#define ER_SQL_DB -11

/**
 * @brief The BramaUzytkownikow class
 * Klasa odpowiadaja za polaczenie z baza danych przechowujaca informacje
 * o uzytkownikach komunikatora
 */
class BramaUzytkownikow : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief sprawdzUzytkownika
     * sprawdza czy użytkownik o podanym ID istnieje
     * @param idUzytkownika ktorego ustnienie chcemy sprawdzic
     * @return true jesli dany uzytkownik istnieje
     */
    bool sprawdzUzytkownika(int idUzytkownika);

    /**
     * @brief sprawdzUzytkownika
     * sprawdza czy użytkownik o podanym nicku (loginie) istnieje
     * @param login uzytkownika ktorego id chcemy poznac
     * @return id uzytkownika jesli istnieje, jesli nie zwraca 0
     */
    int sprawdzUzytkownika(QString login);

    /**
     * @brief getHashPassword
     * zwraca zhashowane hasło użytkownika
     * @param idUzytkownika ktorego hash haslo chcemy poznac
     * @return hash haslo
     */
    QString getHashPassword(int idUzytkownika);

    /**
     * @brief dodajUzytkownika
     * dodaje nowego użytkownika do bazy danych serwera
     * @param login nowego uzytkownika
     * @param hash haslo nowego uzytkownika
     * @return id nowo stworzonego uzytkownika jesli operacja sie powiodla,
     * jesli nie zwraca 0 (login zajety)
     * w razie jakichkolwiek problem z połączaniem z bazą zwraca wartosc ujemna
     * zależna od zaistniałego problemu
     */
    int dodajUzytkownika(QString login, QString hash);

    /**
     * @brief getSharedInstance
     * funkcja zwracajaca wskaznik na jedyna instancje tej klasy
     * @return instancje BramyUzytkownikow
     */
    static BramaUzytkownikow* getSharedInstance();

private:

    /**
     * @brief BramaUzytkownikow
     * Konstruktor od razu probuje otworzyc plik z baza danych i w przypadku
     * nieudanej proby poinformuje o tym w konsoli
     * @param parent
     */
    explicit BramaUzytkownikow(QObject *parent = 0);

    /**
     * @brief BramaUzytkownikow
     *konstruktor kopiujacy, dziala jak domyslny, ale jest definicja zeby byl prywatny
     * @param copy
     */
    BramaUzytkownikow(const BramaUzytkownikow &copy);

    /**
     * @brief instance instancja singletona
     */
    static BramaUzytkownikow* instance;

    /**
     * @brief mutex na operacje dostepu do pliku
     */
    QMutex mutex;

    QSqlDatabase baza;
    
signals:
    
public slots:
    
};

#endif // BRAMAUZYTKOWNIKOW_H
