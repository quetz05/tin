#ifndef OKNOROZMOWY_H
#define OKNOROZMOWY_H

#include <QDialog>
#include <QString>


namespace Ui {
class oknoRozmowy;
}

class oknoRozmowy : public QDialog
{
    Q_OBJECT


private slots:

    void wpisywanieWiadomosci(const QString &);
    void wyslij();
    void zakoncz();

public:
    explicit oknoRozmowy(QWidget *parent = 0, QString login = "", QString rozmowca="");
    ~oknoRozmowy();



signals:
    void koniecRozmowy(const QString&);

    
private:
    Ui::oknoRozmowy *ui;
    QString wiadomosc;
    QString loginTwoj;
    QString loginRozmowcy;

};

#endif // OKNOROZMOWY_H
