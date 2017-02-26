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
    db/connector.cpp \
    dialogaddconsole.cpp \
    db/console.cpp \
    db/daoconsole.cpp

HEADERS  += mainwindow.h \
    db/connector.h \
    dialogaddconsole.h \
    db/console.h \
    db/daoconsole.h

FORMS    += mainwindow.ui \
    dialogaddconsole.ui

RESOURCES += \
    icons.qrc
