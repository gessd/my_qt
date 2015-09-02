#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T21:25:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_client
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    userland.cpp

HEADERS  += dialog.h \
    userland.h

FORMS    += dialog.ui \
    userland.ui
