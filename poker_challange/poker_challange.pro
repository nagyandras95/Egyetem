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
    communitycardselector.cpp \
    cardselector.cpp \
    privatecardselector.cpp \
    amountsetter.cpp \
    gamingtableconfiguration.cpp \
    handevaluator.cpp \
    possibletableevaluator.cpp \
    threadnumbersetdialog.cpp \
    playerwidget.cpp \
    playerscontrolwidget.cpp \
    holdemtypes.cpp

HEADERS  += mainwindow.h \
    card.h \
    combination.h \
    texasholdemmodel.h \
    gamewidget.h \
    communitycardselector.h \
    cardselector.h \
    privatecardselector.h \
    amountsetter.h \
    gamingtableconfiguration.h \
    handevaluator.h \
    ihandevaluator.h \
    threadsafequeue.h \
    possibletableevaluator.h \
    threadnumbersetdialog.h \
    playerwidget.h \
    playerscontrolwidget.h \
    holdemtypes.h
