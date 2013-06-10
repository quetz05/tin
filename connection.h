#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QSocketNotifier>
#include <unistd.h> // to jest wazny include z opcjami read i write

class Connection : public QObject
{
    Q_OBJECT
private:
    int typInformacji;// 1 odczyt 0 zapis -1 blad;
    int gniazdo;
     QWaitCondition powiadomienieGniazda;

public:
    explicit Connection(int soc,QObject *parent = 0);
    /**
     * @brief wyslijPakiet funkcja wysylajaca pakiet na dany socket
     * @param dane wskaznik na dane do wyslania
     * @param dlogosc danych do wyslania
     * @return  0 gdy sie uda -1 w razie bledu
     */
    //int wyslijPakiet(char* dane,int dlogosc);
    /**
     * @brief odbiezPakiet odbiera pakiet z zadanego gniazda
     * @param bufor wskaznik na bufor do zapisu (zaalokowane miejsce o jeden wieksze od ilosci danych)
     * @param dlogosc dlogosc danych do odczytania
     * @return -1 gdy blad 0 w razie sukcesu
     */
    int odbiezPakiet(char*bufor,int dlogosc);

signals:

public slots:
    void wychodzimy();

};

#endif // CONNECTION_H
