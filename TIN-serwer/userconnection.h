#ifndef USERCONECTION_H
#define USERCONECTION_H

#include <QThread>

class UserConnection : public QThread
{
    Q_OBJECT
private:
    int socket;

    //bool wyslijWiadomosc(Naglowek n,QString wiad);
    bool wyslijPakietDanych(char* dane);
protected:
    void run();
public:
    explicit UserConnection(QObject *parent = 0);

    
signals:
    
public slots:
    void nowaWiadomosc(int id);

};

#endif // USERCONECTION_H
