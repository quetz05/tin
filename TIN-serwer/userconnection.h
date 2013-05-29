#ifndef USERCONECTION_H
#define USERCONECTION_H

#include <QThread>

class UserConnection : public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    explicit UserConnection(QObject *parent = 0);

    
signals:
    
public slots:
    
};

#endif // USERCONECTION_H
