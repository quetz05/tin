#include "bramaznajomych.h"

#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QDomDocument>
#include <QDebug>
#include <QDir>

QString BramaZnajomych::katalogBazy = "Baza";

BramaZnajomych::BramaZnajomych(QString login ,QObject *parent) :
    QObject(parent)
{
//    qDebug() << katalogBazy;
    this->login = login;
    wczytajBaze();
}

QList<Znajomy> BramaZnajomych::getListaZnajomych()
{
    return listaZnajomych;
}

bool BramaZnajomych::czyWBazie(int idUzytkownika)
{
    QList< Znajomy >::Iterator it, koniec;
    koniec = listaZnajomych.end();

    for(it = listaZnajomych.begin(); it < koniec; ++it){
        if(it->second == idUzytkownika){
            return true;
        }
    }
    return false;
}

bool BramaZnajomych::dodajZnajomego(int idUzytkownika, QString nazwaUzytkownika)
{
    Znajomy nowy(nazwaUzytkownika, idUzytkownika);

    if(listaZnajomych.contains(nowy)){
//        qDebug() << "Znajomy juz jest w bazie";
        return false;
    }

//    qDebug() << "Dodaje: " << nowy;

    QList< Znajomy >::Iterator it, koniec;
    koniec = listaZnajomych.end();
    bool dodany = false;
    for(it = listaZnajomych.begin(); it < koniec; ++it){
//        qDebug() << "Porownanie: " << (nowy.first.compare( it->first) < 0) ;
        if(nowy.first.compare( it->first) < 0){
//            --it;
            listaZnajomych.insert(it, nowy);
            dodany = true;
            break;
        }
    }

    if(!dodany){
        listaZnajomych.push_back(nowy);
//        qDebug() << "Dodaje na koncu ";
    }

    zapiszBaze();

    test();

    return true;
}

bool BramaZnajomych::usunZnajomego(int idUzytkownika)
{
    QList< Znajomy >::Iterator it, koniec;
    koniec = listaZnajomych.end();

    for(it = listaZnajomych.begin(); it < koniec; ++it){
        if(it->second == idUzytkownika){
            listaZnajomych.erase(it);
            zapiszBaze();
            test();
            return true;
        }
    }
    return false;
}


bool BramaZnajomych::wczytajBaze()
{
    QFile plikSchematu(":/znajomi.xsd");
    plikSchematu.open(QIODevice::ReadOnly);
    QXmlSchema schemat;
    schemat.load(&plikSchematu, QUrl::fromLocalFile(plikSchematu.fileName()));

    if(schemat.isValid()){
//        qDebug() << "Schemat Poprawny";
        QString sciezka(katalogBazy);
        sciezka.append("/");
        sciezka.append(login);
        sciezka.append(".xml");
//        qDebug() << sciezka;
        plikBazy = new QFile(sciezka);

        if(plikBazy->open(QIODevice::ReadOnly)){
//            qDebug() << "Plik istnieje";

            QXmlSchemaValidator walidator(schemat);
            if(walidator.validate(plikBazy, QUrl::fromLocalFile(plikBazy->fileName()))){
//                qDebug() << "Plik porawny";

                plikBazy->close();
                plikBazy->open(QIODevice::ReadOnly);

                QDomDocument doc("mydocument");
                if(doc.setContent(plikBazy)){
//                    qDebug() << "Udalo sie zaladowac document";
                } else {
//                    qDebug() << "DomDocument fejl";
                }


                QDomElement glownyElement = doc.documentElement();

                QDomNodeList znajomi = glownyElement.elementsByTagName("znajomy");
                int iloscZnajomych = znajomi.size();

//                qDebug() << "Ilosc znajomych w pliku xml: " << iloscZnajomych;

                for(int i = 0; i < iloscZnajomych; ++i){
                    int id = znajomi.at(i).attributes().namedItem("ID").toAttr().value().toInt();
                    QString nick = znajomi.at(i).attributes().namedItem("login").toAttr().value();
                    listaZnajomych.push_back(qMakePair(nick, id));
                }

//                test();


            } else{
//                qDebug() << "Poprawnosc pliku xml fejl";
                plikBazy->close();
                zapiszBaze();

            }
        } else {
//            qDebug() << "Plik xml nie istnieje";
            QDir katalog(katalogBazy);
            if(!katalog.exists()){
//                qDebug() << "Katalog bazodanowy nie istnieje";
                if(katalog.mkpath(".")){
//                    qDebug() << "Stworzono katalog bazodanowy";
                } else{
//                    qDebug() << "Proba stworzenia katalogu bazodanowego fejl";

                }
            }
            plikBazy->close();
            zapiszBaze();


        }
    } else {
//        qDebug() << "Schemat fejl";
        return false;

    }

    plikSchematu.close();
    plikBazy->close();


    usunZnajomego(555);

    return true;
}

bool BramaZnajomych::zapiszBaze()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("znajomi");



    QList< Znajomy >::ConstIterator it, koniec;
    koniec = listaZnajomych.cend();
    for(it = listaZnajomych.cbegin(); it < koniec; ++it){
        QDomElement znajomy = doc.createElement("znajomy");
        znajomy.setAttribute("login", it->first);
        znajomy.setAttribute("ID", it->second);
        root.appendChild(znajomy);
    }

    doc.appendChild(root);

    QString xml = doc.toString();



    if(plikBazy->open(QIODevice::WriteOnly)){
        QTextStream stream(plikBazy);
        stream << xml;
        stream.flush();
        plikBazy->close();
    }else{
//        qDebug() << "Zapisz do pliku fejl";
        return false;
    }

//    qDebug() <<  "Zapisano do pliku";

    return true;

}



void BramaZnajomych::test()
{
    QList< Znajomy >::ConstIterator it;

    for(it = listaZnajomych.cbegin(); it < listaZnajomych.cend(); ++it){
        qDebug() << *it;
    }

}

BramaZnajomych::~BramaZnajomych()
{
    delete plikBazy;
}
