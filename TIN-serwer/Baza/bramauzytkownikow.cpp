#include "bramauzytkownikow.h"
#include <qdebug.h>

#include <QSqlQuery>
#include <QSqlResult>

BramaUzytkownikow* BramaUzytkownikow::instance = 0L;

BramaUzytkownikow::BramaUzytkownikow(QObject *parent) :
    QObject(parent)
{
    baza = QSqlDatabase::addDatabase("QSQLITE");
    baza.setDatabaseName("uzytkownicy.sqlite");

    if(baza.open()){
        qDebug() << "Udalo sie otworzyc plik z baza!";
        baza.close();
    } else {
        qDebug() << "Polaczenie z baza fejl!";
    }
}

BramaUzytkownikow::BramaUzytkownikow(const BramaUzytkownikow &copy)
{
}



bool BramaUzytkownikow::sprawdzUzytkownika(int idUzytkownika)
{
    if(getHashPassword(idUzytkownika).size())
        return true;
    return false;
}


int BramaUzytkownikow::dodajUzytkownika(QString login, QString hash)
{
    QString insert = "INSERT INTO uzytkownicy VALUES ( null, '";
    insert.append(login);
    insert.append("','");
    insert.append(hash);
    insert.append("');");

    mutex.lock();

    if(baza.open()){
        qDebug() << "Udalo sie otworzyc plik z baza!";
        baza.transaction();
        QSqlQuery dodaj(baza);
        dodaj.prepare(insert);
        if(dodaj.exec()){
            qDebug() << "Udalo sie dodac uzytkownika!";
            baza.commit();
        } else{
            qDebug() << "Dodawanie uzytkownika fejl";
            baza.rollback();

            mutex.unlock();
            return 0;
        }

        baza.close();
    } else {
        qDebug() << "Polaczenie z baza fejl!";
        mutex.unlock();
        return ER_OPEN_DB;
    }

    mutex.unlock();
    return sprawdzUzytkownika(login);
}

BramaUzytkownikow *BramaUzytkownikow::getSharedInstance()
{
    if(!instance)
        instance = new BramaUzytkownikow;
    return instance;
}


int BramaUzytkownikow::sprawdzUzytkownika(QString login)
{
    QString select = "SELECT id FROM uzytkownicy where login = '";
    select.append(login);
    select.append("';");

    int id;

    mutex.lock();
    if(baza.open()){
        baza.transaction();
        QSqlQuery pobierzID(baza);
        pobierzID.prepare(select);
        if(pobierzID.exec()){

            if(pobierzID.next()){
            qDebug() << "Udalo sie pobrac ID: " << pobierzID.value(0).toString();
            baza.commit();

            id = pobierzID.value(0).toString().toInt();
            } else {

            qDebug () << "Uzytkownik o danym loginie nie istnieje";
            id =  0;
            }

        } else{
            qDebug() << "Pobranie ID fejl";
            baza.rollback();
            id = ER_SQL_DB;
        }
    } else{
        mutex.unlock();
        return ER_OPEN_DB;
    }

    baza.close();
    mutex.unlock();
    return id;

}

QString BramaUzytkownikow::getHashPassword(int idUzytkownika)
{
    QString select = "SELECT haslo FROM uzytkownicy where id = ";
    select.append(QString::number(idUzytkownika));
    select.append(";");

    QString haslo;

    mutex.lock();
    if(baza.open()){
        baza.transaction();
        QSqlQuery pobierzHaslo(baza);
        pobierzHaslo.prepare(select);
        if(pobierzHaslo.exec()){

            if(pobierzHaslo.next()){
            qDebug() << "Udalo sie pobrac haslo: " << pobierzHaslo.value(0).toString();
            baza.commit();
            haslo = pobierzHaslo.value(0).toString();
            } else{

                qDebug () << "Uzytkownik o danym id nie istnieje";

            }

        } else{
            qDebug() << "Pobranie hasla fejl";
            baza.rollback();
        }
    }

    baza.close();
    mutex.unlock();
    return haslo;
}
