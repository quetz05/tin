#ifndef WYSZUKIWARKA_H
#define WYSZUKIWARKA_H

#include <QDialog>

namespace Ui {
class wyszukiwarka;
}

class wyszukiwarka : public QDialog
{
    Q_OBJECT
    
public:
    explicit wyszukiwarka(QWidget *parent = 0);
    ~wyszukiwarka();
    
private:
    Ui::wyszukiwarka *ui;
};

#endif // WYSZUKIWARKA_H
