#include "test.h"
#include <QDebug>
#include <QDebug>
Test::Test()
{
}

void Test::test1()
{// test wiadomosci
    message wiadomosc("jakas zarombista wiadomosc");
    QVERIFY(wiadomosc.iluPrzeczytalo()==0);
    qDebug() << wiadomosc.Czytaj(1);
    QVERIFY(wiadomosc.iluPrzeczytalo());

}

void Test::test2()
{

}

void Test::test3()
{

}
