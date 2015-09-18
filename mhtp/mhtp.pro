#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T14:51:36
#
#-------------------------------------------------

QT       += core gui webkit
QT+=sql
QT+=network
QT+=script
QT+=xml
CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mhtp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tskpage.cpp

HEADERS  += mainwindow.h \
    tskpage.h

FORMS    += mainwindow.ui
