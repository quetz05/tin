/********************************************************************************
** Form generated from reading UI file 'ekranlogowania.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EKRANLOGOWANIA_H
#define UI_EKRANLOGOWANIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ekranLogowania
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *textLogin;
    QLabel *label_2;
    QLineEdit *textPass;
    QPushButton *pushZaloguj;
    QPushButton *pushZakoncz;
    QPushButton *pushRejestruj;

    void setupUi(QDialog *ekranLogowania)
    {
        if (ekranLogowania->objectName().isEmpty())
            ekranLogowania->setObjectName(QStringLiteral("ekranLogowania"));
        ekranLogowania->resize(379, 252);
        verticalLayoutWidget = new QWidget(ekranLogowania);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 341, 121));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        textLogin = new QLineEdit(verticalLayoutWidget);
        textLogin->setObjectName(QStringLiteral("textLogin"));

        verticalLayout->addWidget(textLogin);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        textPass = new QLineEdit(verticalLayoutWidget);
        textPass->setObjectName(QStringLiteral("textPass"));

        verticalLayout->addWidget(textPass);

        pushZaloguj = new QPushButton(ekranLogowania);
        pushZaloguj->setObjectName(QStringLiteral("pushZaloguj"));
        pushZaloguj->setGeometry(QRect(20, 170, 141, 23));
        pushZakoncz = new QPushButton(ekranLogowania);
        pushZakoncz->setObjectName(QStringLiteral("pushZakoncz"));
        pushZakoncz->setGeometry(QRect(280, 170, 80, 23));
        pushRejestruj = new QPushButton(ekranLogowania);
        pushRejestruj->setObjectName(QStringLiteral("pushRejestruj"));
        pushRejestruj->setGeometry(QRect(170, 170, 101, 23));

        retranslateUi(ekranLogowania);

        QMetaObject::connectSlotsByName(ekranLogowania);
    } // setupUi

    void retranslateUi(QDialog *ekranLogowania)
    {
        ekranLogowania->setWindowTitle(QApplication::translate("ekranLogowania", "Super TIN-TIN", 0));
        label->setText(QApplication::translate("ekranLogowania", "Login:", 0));
        label_2->setText(QApplication::translate("ekranLogowania", "Has\305\202o:", 0));
        pushZaloguj->setText(QApplication::translate("ekranLogowania", "Zaloguj", 0));
        pushZakoncz->setText(QApplication::translate("ekranLogowania", "Wyjd\305\272", 0));
        pushRejestruj->setText(QApplication::translate("ekranLogowania", "Rejestracja", 0));
    } // retranslateUi

};

namespace Ui {
    class ekranLogowania: public Ui_ekranLogowania {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EKRANLOGOWANIA_H
