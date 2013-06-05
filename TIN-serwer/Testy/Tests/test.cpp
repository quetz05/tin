#include "test.h"
#include <QDebug>

Test::Test()
{
}

void Test::test1()
{// test wiadomosci
    message wiadomosc("jakas zarombista wiadomosc");
    QVERIFY2(wiadomosc.iluPrzeczytalo()==0);
    QDebug() << wiadomosc.Czytaj();
    QVERIFY2(wiadomosc.iluPrzeczytalo());

}

void Test::test2()
{

}

void Test::test3()
{

}
