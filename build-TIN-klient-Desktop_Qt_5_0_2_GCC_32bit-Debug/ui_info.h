/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_info
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *informacja;
    QPushButton *pushOK;
    QGraphicsView *picture;

    void setupUi(QDialog *info)
    {
        if (info->objectName().isEmpty())
            info->setObjectName(QStringLiteral("info"));
        info->resize(400, 137);
        verticalLayoutWidget = new QWidget(info);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 10, 311, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        informacja = new QPlainTextEdit(verticalLayoutWidget);
        informacja->setObjectName(QStringLiteral("informacja"));

        verticalLayout->addWidget(informacja);

        pushOK = new QPushButton(info);
        pushOK->setObjectName(QStringLiteral("pushOK"));
        pushOK->setGeometry(QRect(160, 100, 80, 23));
        picture = new QGraphicsView(info);
        picture->setObjectName(QStringLiteral("picture"));
        picture->setGeometry(QRect(10, 10, 61, 81));

        retranslateUi(info);

        QMetaObject::connectSlotsByName(info);
    } // setupUi

    void retranslateUi(QDialog *info)
    {
        info->setWindowTitle(QApplication::translate("info", "Okno informacji", 0));
        pushOK->setText(QApplication::translate("info", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class info: public Ui_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
