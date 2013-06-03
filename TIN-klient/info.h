#ifndef INFO_H
#define INFO_H

#include <QDialog>

namespace Ui {
class info;
}

 /**
    * @brief The info class
    * Klasa okna informacyjnego
    */
class info : public QDialog
{
    Q_OBJECT
    
public:
 /**
    * @brief info
    * Konstruktor budujacy okno o danej wiadomosci i zaleznie od wartosci ok - okreslajacej czy informacja
    * jest pozytywna czy negatywna
    */
    explicit info(QWidget *parent = 0, QString info = "", bool ok = false);
    ~info();

signals:
    void SIGzamknij();

public slots:
    void zakoncz();
    
private:
    Ui::info *ui;

};

#endif // INFO_H
