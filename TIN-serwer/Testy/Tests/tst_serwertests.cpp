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

int main(int argc, char** argv)
{
   int status = 0;
   {
      Test tc;
      status |= QTest::qExec(&tc, argc, argv);
   }
   {
      Test tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   return status;
}

#include "tst_serwertests.moc"
