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
    db/daoconsole.cpp \
    dialoggame.cpp \
    db/daogames.cpp \
    db/game.cpp \
    gamerunner.cpp

HEADERS  += mainwindow.h \
    db/connector.h \
    dialogaddconsole.h \
    db/console.h \
    db/daoconsole.h \
    dialoggame.h \
    db/daogames.h \
    db/game.h \
    gamerunner.h

FORMS    += mainwindow.ui \
    dialogaddconsole.ui \
    dialoggame.ui

RESOURCES += \
    icons.qrc
