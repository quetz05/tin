/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSzukajZnajomych;
    QAction *actionZakoncz;
    QAction *actionWyloguj;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushSzukajZnajomych;
    QListWidget *listaZnajomych;
    QLabel *titListaZnajomych;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushDodaj;
    QPushButton *pushUsun;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushGrupRozmawiaj;
    QPushButton *pushWyslijPlik;
    QPushButton *pushGrupWyslijPlik;
    QGraphicsView *logoView;
    QMenuBar *menuBar;
    QMenu *menuPlik;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(543, 385);
        actionSzukajZnajomych = new QAction(MainWindow);
        actionSzukajZnajomych->setObjectName(QStringLiteral("actionSzukajZnajomych"));
        actionZakoncz = new QAction(MainWindow);
        actionZakoncz->setObjectName(QStringLiteral("actionZakoncz"));
        actionWyloguj = new QAction(MainWindow);
        actionWyloguj->setObjectName(QStringLiteral("actionWyloguj"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(330, 0, 204, 321));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushSzukajZnajomych = new QPushButton(gridLayoutWidget);
        pushSzukajZnajomych->setObjectName(QStringLiteral("pushSzukajZnajomych"));

        gridLayout->addWidget(pushSzukajZnajomych, 4, 0, 1, 1);

        listaZnajomych = new QListWidget(gridLayoutWidget);
        listaZnajomych->setObjectName(QStringLiteral("listaZnajomych"));

        gridLayout->addWidget(listaZnajomych, 1, 0, 1, 1);

        titListaZnajomych = new QLabel(gridLayoutWidget);
        titListaZnajomych->setObjectName(QStringLiteral("titListaZnajomych"));

        gridLayout->addWidget(titListaZnajomych, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushDodaj = new QPushButton(gridLayoutWidget);
        pushDodaj->setObjectName(QStringLiteral("pushDodaj"));

        horizontalLayout_2->addWidget(pushDodaj);

        pushUsun = new QPushButton(gridLayoutWidget);
        pushUsun->setObjectName(QStringLiteral("pushUsun"));

        horizontalLayout_2->addWidget(pushUsun);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 210, 191, 131));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushGrupRozmawiaj = new QPushButton(verticalLayoutWidget);
        pushGrupRozmawiaj->setObjectName(QStringLiteral("pushGrupRozmawiaj"));

        verticalLayout_4->addWidget(pushGrupRozmawiaj);

        pushWyslijPlik = new QPushButton(verticalLayoutWidget);
        pushWyslijPlik->setObjectName(QStringLiteral("pushWyslijPlik"));

        verticalLayout_4->addWidget(pushWyslijPlik);

        pushGrupWyslijPlik = new QPushButton(verticalLayoutWidget);
        pushGrupWyslijPlik->setObjectName(QStringLiteral("pushGrupWyslijPlik"));

        verticalLayout_4->addWidget(pushGrupWyslijPlik);

        logoView = new QGraphicsView(centralWidget);
        logoView->setObjectName(QStringLiteral("logoView"));
        logoView->setGeometry(QRect(30, 20, 256, 192));
        logoView->setInteractive(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 543, 20));
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QStringLiteral("menuPlik"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPlik->menuAction());
        menuPlik->addAction(actionSzukajZnajomych);
        menuPlik->addSeparator();
        menuPlik->addAction(actionWyloguj);
        menuPlik->addAction(actionZakoncz);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Super TIN-TIN", 0));
        actionSzukajZnajomych->setText(QApplication::translate("MainWindow", "Szukaj znajomych", 0));
        actionZakoncz->setText(QApplication::translate("MainWindow", "Zako\305\204cz", 0));
        actionWyloguj->setText(QApplication::translate("MainWindow", "Wyloguj", 0));
        pushSzukajZnajomych->setText(QApplication::translate("MainWindow", "Szukaj znajomych", 0));
        titListaZnajomych->setText(QApplication::translate("MainWindow", "Lista znajomych", 0));
        pushDodaj->setText(QApplication::translate("MainWindow", "Dodaj", 0));
        pushUsun->setText(QApplication::translate("MainWindow", "Usu\305\204", 0));
        pushGrupRozmawiaj->setText(QApplication::translate("MainWindow", "Rozmowa", 0));
        pushWyslijPlik->setText(QApplication::translate("MainWindow", "Wyslij plik", 0));
        pushGrupWyslijPlik->setText(QApplication::translate("MainWindow", "Grupowe wysy\305\202anie", 0));
        menuPlik->setTitle(QApplication::translate("MainWindow", "Plik", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
