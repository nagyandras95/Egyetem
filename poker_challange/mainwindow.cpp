#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combination.h"
#include "card.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(500,500);
    setWindowTitle(trUtf8("Texas Hold'em Poker Assist"));

    _newGameAction = new QAction(trUtf8("Start"), this);
    _newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    _newGameAction->setStatusTip(trUtf8("Starting new game"));


    _configureAction = new QAction(trUtf8("&Configuration"), this);
    _configureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    _configureAction->setStatusTip(trUtf8("Configue starting state"));

    _exitAction = new QAction(trUtf8("&Exit"), this);
    _exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _exitAction->setStatusTip(trUtf8("Exiting from assistant"));

    _gameMenu = menuBar()->addMenu(trUtf8("&Game"));
    _gameMenu->addAction(_newGameAction);
    _gameMenu->addAction(_configureAction);
    _gameMenu->addSeparator();
    _gameMenu->addAction(_exitAction);

    _infoMenu = menuBar()->addMenu(trUtf8("&Info"));

    _gameWidget = new GameWidget(this);
    setCentralWidget(_gameWidget);
}

MainWindow::~MainWindow()
{
    //delete ui;
}
