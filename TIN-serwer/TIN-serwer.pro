#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T13:35:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TIN-serwer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Baza/bramauzytkownikow.cpp \
    serwerapp.cpp \
    rozmowa.cpp \
    message.cpp \
    userconnection.cpp

HEADERS  += mainwindow.h \
    Baza/bramauzytkownikow.h \
    serwerapp.h \
    userconnection.h \
    rozmowa.h \
    message.h \
    ../wiadomosc.h

FORMS    += mainwindow.ui
