#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T15:23:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wl_tcpServer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    sqlQuery.cpp

HEADERS  += dialog.h \
    sqlQuery.h

FORMS    += dialog.ui
