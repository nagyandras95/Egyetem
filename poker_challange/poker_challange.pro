#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T15:22:20
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = poker_challange
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    card.cpp \
    combination.cpp \
    texasholdemmodel.cpp \
    gamewidget.cpp \
    hand_evaluator.cpp \
    ihand_evaluator.cpp \
    game_configuration.cpp \
    communitycardselector.cpp

HEADERS  += mainwindow.h \
    card.h \
    combination.h \
    texasholdemmodel.h \
    gamewidget.h \
    hand_evaluator.h \
    ihand_evaluator.h \
    game_configuration.h \
    communitycardselector.h

FORMS    += mainwindow.ui
