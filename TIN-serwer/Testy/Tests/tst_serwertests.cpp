#include <QString>
#include <QtTest>
#include "../message.h"

class SerwerTests : public QObject
{
    Q_OBJECT
    
public:
    SerwerTests();
    
private Q_SLOTS:
    void testCase1();
};

SerwerTests::SerwerTests()
{
}

void SerwerTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SerwerTests)

#include "tst_serwertests.moc"