/********************************************************************************
** Form generated from reading UI file 'wyszukiwarka.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYSZUKIWARKA_H
#define UI_WYSZUKIWARKA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wyszukiwarka
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *Wyszukiwarka)
    {
        if (Wyszukiwarka->objectName().isEmpty())
            Wyszukiwarka->setObjectName(QStringLiteral("Wyszukiwarka"));
        Wyszukiwarka->resize(357, 252);
        buttonBox = new QDialogButtonBox(Wyszukiwarka);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-70, 210, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(Wyszukiwarka);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 211, 166));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setFrameShape(QFrame::Box);
        label_3->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(label_3);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(Wyszukiwarka);
        QObject::connect(buttonBox, SIGNAL(accepted()), Wyszukiwarka, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Wyszukiwarka, SLOT(reject()));

        QMetaObject::connectSlotsByName(Wyszukiwarka);
    } // setupUi

    void retranslateUi(QDialog *Wyszukiwarka)
    {
        Wyszukiwarka->setWindowTitle(QApplication::translate("Wyszukiwarka", "Wyszukiwarka znajomych", 0));
        label_3->setText(QApplication::translate("Wyszukiwarka", "Wpisz dane do wyszukiwania:", 0));
        label->setText(QApplication::translate("Wyszukiwarka", "Nick:", 0));
        label_2->setText(QApplication::translate("Wyszukiwarka", "ID:", 0));
        pushButton->setText(QApplication::translate("Wyszukiwarka", "Wyszukaj", 0));
    } // retranslateUi

};

namespace Ui {
    class Wyszukiwarka: public Ui_Wyszukiwarka {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYSZUKIWARKA_H
