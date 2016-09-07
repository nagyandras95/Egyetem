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
    gamewidget.cpp \
    communitycardselector.cpp \
    cardselector.cpp \
    privatecardselector.cpp \
    amountsetter.cpp \
    threadnumbersetdialog.cpp \
    playerwidget.cpp \
    playerscontrolwidget.cpp \
    model/card.cpp \
    model/combination.cpp \
    model/gamingtableconfiguration.cpp \
    model/handevaluator.cpp \
    model/holdemtypes.cpp \
    model/possibletableevaluator.cpp \
    model/texasholdemmodel.cpp \
    model/strageist.cpp \
    model/pair.cpp \
    decesionmatcher.cpp \
    cardvaluematcher.cpp \
    cardcolormatcher.cpp \

HEADERS  += mainwindow.h \
    gamewidget.h \
    communitycardselector.h \
    cardselector.h \
    privatecardselector.h \
    amountsetter.h \
    threadnumbersetdialog.h \
    playerwidget.h \
    playerscontrolwidget.h \
    model/card.h \
    model/combination.h \
    model/gamingtableconfiguration.h \
    model/handevaluator.h \
    model/holdemtypes.h \
    model/ihandevaluator.h \
    model/player.h \
    model/possibletableevaluator.h \
    model/texasholdemmodel.h \
    model/strageist.h \
    model/threadsafequeue.h \
    model/pair.h \
    model/possiblestate.h \
    modelviewmatching.h \
    decesionmatcher.h \
    cardvaluematcher.h \
    cardcolormatcher.h \    
    model/itexasholdemmodel.h
