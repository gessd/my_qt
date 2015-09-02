#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T16:45:34
#
#-------------------------------------------------

QT       += core gui
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_sqlite
TEMPLATE = app

LIBS+=-L E:/code/ddk/251/SKProxy/ -lsqlite3

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    sqlite3.h

FORMS    += mainwindow.ui
