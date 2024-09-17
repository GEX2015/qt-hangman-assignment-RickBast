#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T13:41:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hangman
TEMPLATE = app

SOURCES += main.cpp\
        controller/mainwindow.cpp \
    model/hangman.cpp

HEADERS  += controller/mainwindow.h \
    model/hangman.h

FORMS    += view/mainwindow.ui

RESOURCES += \
    resrouces.qrc
