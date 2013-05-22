/********************************************************************************
** Form generated from reading UI file 'dodawanie.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DODAWANIE_H
#define UI_DODAWANIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dodawanie
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelID;
    QLineEdit *ID;
    QLabel *labelNick;
    QLineEdit *Nick;
    QPushButton *pushDodaj;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushOK;
    QGraphicsView *picture;

    void setupUi(QDialog *dodawanie)
    {
        if (dodawanie->objectName().isEmpty())
            dodawanie->setObjectName(QStringLiteral("dodawanie"));
        dodawanie->resize(273, 322);
        verticalLayoutWidget = new QWidget(dodawanie);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 110, 211, 211));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelID = new QLabel(verticalLayoutWidget);
        labelID->setObjectName(QStringLiteral("labelID"));

        verticalLayout->addWidget(labelID);

        ID = new QLineEdit(verticalLayoutWidget);
        ID->setObjectName(QStringLiteral("ID"));

        verticalLayout->addWidget(ID);

        labelNick = new QLabel(verticalLayoutWidget);
        labelNick->setObjectName(QStringLiteral("labelNick"));

        verticalLayout->addWidget(labelNick);

        Nick = new QLineEdit(verticalLayoutWidget);
        Nick->setObjectName(QStringLiteral("Nick"));

        verticalLayout->addWidget(Nick);

        pushDodaj = new QPushButton(verticalLayoutWidget);
        pushDodaj->setObjectName(QStringLiteral("pushDodaj"));

        verticalLayout->addWidget(pushDodaj);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushOK = new QPushButton(verticalLayoutWidget);
        pushOK->setObjectName(QStringLiteral("pushOK"));

        verticalLayout->addWidget(pushOK);

        picture = new QGraphicsView(dodawanie);
        picture->setObjectName(QStringLiteral("picture"));
        picture->setGeometry(QRect(70, 10, 131, 101));

        retranslateUi(dodawanie);

        QMetaObject::connectSlotsByName(dodawanie);
    } // setupUi

    void retranslateUi(QDialog *dodawanie)
    {
        dodawanie->setWindowTitle(QApplication::translate("dodawanie", "Dodaj znajomego", 0));
        labelID->setText(QApplication::translate("dodawanie", "ID", 0));
        labelNick->setText(QApplication::translate("dodawanie", "Nick", 0));
        pushDodaj->setText(QApplication::translate("dodawanie", "Dodaj", 0));
        pushOK->setText(QApplication::translate("dodawanie", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class dodawanie: public Ui_dodawanie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DODAWANIE_H
