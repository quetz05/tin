#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T18:54:52
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_serwertests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_serwertests.cpp \
    ../../message.cpp \
    test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../message.h \
    test.h
