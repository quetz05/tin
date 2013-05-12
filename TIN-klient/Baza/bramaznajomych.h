#ifndef BRAMAZNAJOMYCH_H
#define BRAMAZNAJOMYCH_H

#include <QObject>
#include <QPair>
#include <QList>
#include <QFile>

/**
 * Znajomy przedstawiony jako para
 * first->login
 * second->id
 */
typedef QPair< QString, int > Znajomy;

class BramaZnajomych : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief BramaZnajomych
     * Podczas konstrukcji laduje baze z pliku dla konkretnego uzytkownika z katalogu katalogBazy
     * jesli taki plik nie istnieje, tworzy taki plik z pusta lista
     * jesli nie istnieje tez katalog z baza, tworzy katalog dla baz
     * jesli plik istnieje, ale nie jest poprawnym plikiem xml dla aplikacji
     * nadpisuje go pusta lista
     * @param login uzytkownika dla ktorege potrzebna jest baza
     * @param parent
     */
    explicit BramaZnajomych(QString login, QObject *parent = 0);

    /**
     * @brief getListaZnajomych
     * @return kopia listy znajomych
     */
    QList< Znajomy > getListaZnajomych();

    /**
     * @brief czyWBazie
     * funkcja sprawdzająca czy dany znajomy jest już w bazie
     * @param idUzytkownika
     * @return true jesli znajomy jest w bazie
     */
    bool czyWBazie(int idUzytkownika);

    /**
     * @brief dodajZnajomego
     * funkcja dodająca do lokalnej bazy danych znajomego
     * @param idUzytkownika
     * @return true jesli operacja sie powiodla
     */
    bool dodajZnajomego(int idUzytkownika, QString nazwaUzytkownika);

    /**
     * @brief usunZnajomego
     * funkcja usuwająca użytkownika z lokalnej bazy danych znajomych
     * @param idUzytkownika
     * @return true jesli operacja sie powiodla
     */
    bool usunZnajomego(int idUzytkownika);

    /**
     * @brief test
     * drukuje do konsoli liste znajomych
     */
    void test();

    virtual ~BramaZnajomych();

private:
    /**
     * @brief katalogBazy
     * nazwa katalogu w ktorym przechowywane pliki bazodanowe
     */
    static QString katalogBazy;

    /**
     * @brief login
     * login uzytkownika, ktorego baza jest obsługiwana przez obiekt
     */
    QString login;

    /**
     * @brief listaZnajomych
     * lista znajomych będąca odwzorowana z tej ktora jest na dysku
     */
    QList< Znajomy > listaZnajomych;

    /**
     * @brief plikBazy
     * wskaznik na plik z baza danych
     */
    QFile *plikBazy;

    /**
     * @brief wczytajBaze
     * wczytuje baze z odpowiedniego pliku dla uzytkownika
     * @return
     */
    bool wczytajBaze();

    /**
     * @brief zapiszBaze
     * zapisuje baze do odpowiedniego pliku dla uzytkownika
     * @return
     */
    bool zapiszBaze();
    
signals:
    
public slots:
    
};

#endif // BRAMAZNAJOMYCH_H
