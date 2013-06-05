#ifndef TEST_H
#define TEST_H
#include "../../message.h"


#include <QObject>
#include <QTest>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test();

signals:

private Q_SLOTS:
    void test1();
    void test2();
    void test3();

};

#endif // TEST_H
