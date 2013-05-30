#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QMap>
/**
 * @brief The message class
 *  klasa przechowująca wiadomość oraz dane kto ją przeczytał
 */
class message
{
private:

    QMap<int,bool> przeczytali;
    QString wiadomosc;
public:
    /**
     * @brief message domyślny konstruktor wiadomosci razem ze stringiem ja zawierajacym
     * @param wiadomosc string wiadomosci
     */
    explicit message(QString wiadomosc= "0");
    /**
     * @brief czyPrzeczytal sprawdzamy czy dany watek juz czytal ta wiadomosc
     * @param k id czytajacego
     * @return czy przeczytal
     */
    bool czyPrzeczytal(int k){return przeczytali.contains(k);  }//sprawdzamy czy dany koles przeczytal nasza wiadomosc
    /**
     * @brief Czytaj funkcja umozliwiajaca czytanie wiadomosci przez danego urzytkownika
     * @param id urzytkownika
     * @return napis z wiadomoscia
     */
    QString Czytaj(int id); //odczytujemy wiadomość ze wskazaniem na to
    /**
     * @brief usunInf usuwamy info o kims kto to czytal
     * @param id id tego kogos
     */
    void usunInf(int id);
    /**
     * @brief iluPrzeczytalo zliczarka ilu ludzi przeczytalo i czy przypadkiem nie wszyscy rozmowcy
     * @return liczba przeczytajacych ludzi
     */
    int iluPrzeczytalo(){return przeczytali.size();}

};

#endif // MESSAGE_H
