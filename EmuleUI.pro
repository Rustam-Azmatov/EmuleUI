#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T18:11:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmuleUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db/connector.cpp

HEADERS  += mainwindow.h \
    db/connector.h

FORMS    += mainwindow.ui
