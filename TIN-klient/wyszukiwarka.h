#ifndef WYSZUKIWARKA_H
#define WYSZUKIWARKA_H

#include <QDialog>

namespace Ui {
class Wyszukiwarka;
}

class wyszukiwarka : public QDialog
{
    Q_OBJECT
    
public:
    explicit wyszukiwarka(QWidget *parent = 0);
    ~wyszukiwarka();
    
private:
    Ui::Wyszukiwarka *ui;
};

#endif // WYSZUKIWARKA_H
