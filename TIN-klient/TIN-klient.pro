#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T13:49:13
#
#-------------------------------------------------

QT       += core gui
QT      += xmlpatterns
QT      += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TIN-klient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Baza/bramaznajomych.cpp

HEADERS  += mainwindow.h \
    Baza/bramaznajomych.h

FORMS    += mainwindow.ui

RESOURCES += \
    Baza/znajomi_zasoby.qrc
