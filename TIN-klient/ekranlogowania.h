#ifndef EKRANLOGOWANIA_H
#define EKRANLOGOWANIA_H

#include <QDialog>
#include <QString>
#include <mainwindow.h>
#include "info.h"

namespace Ui {
class ekranLogowania;
}

class ekranLogowania : public QDialog
{
    Q_OBJECT


private slots:

    void czytajLogin(QString);
    void czytajHaslo(QString);
    void zakoncz();
    void zaloguj();
    void rejestruj();
    
public:
    explicit ekranLogowania(QWidget *parent = 0);
    ~ekranLogowania();
    QString pobierzLogin();
    bool dostep;
    
private:
    QString login;
    QString haslo;

    info *oknoInformacji;

    Ui::ekranLogowania *ui;
};

#endif // EKRANLOGOWANIA_H
