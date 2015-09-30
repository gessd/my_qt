#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T17:39:45
#
#-------------------------------------------------

QT       += core gui
QT+=network
QT+=script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_qtjson
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
