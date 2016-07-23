#include "mainwindow.h"
#include "combination.h"
#include "card.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //setMinimumSize(400,400);
    setWindowTitle(trUtf8("Texas Hold'em Poker Assist"));

    _newGameAction = new QAction(trUtf8("Start"), this);
    _newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    _newGameAction->setStatusTip(trUtf8("Starting new game"));

    _hintAction = new QAction(trUtf8("Hint"),this);
    _hintAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    _hintAction->setStatusTip(trUtf8("Adding the next hint"));


    _configureAction = new QAction(trUtf8("&Configuration"), this);
    _configureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    _configureAction->setStatusTip(trUtf8("Configue starting state"));

    _exitAction = new QAction(trUtf8("&Exit"), this);
    _exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _exitAction->setStatusTip(trUtf8("Exiting from assistant"));

    _gameMenu = menuBar()->addMenu(trUtf8("&Game"));
    _gameMenu->addAction(_hintAction);
    _gameMenu->addAction(_configureAction);
    _gameMenu->addSeparator();
    _gameMenu->addAction(_exitAction);

    _infoMenu = menuBar()->addMenu(trUtf8("&Info"));

    _gameWidget = new GameWidget(this);
    setCentralWidget(_gameWidget);

    connect(_hintAction,SIGNAL(triggered()),_gameWidget,SLOT(getHint()));

    connect(_gameWidget, SIGNAL(hintAdded(QString)), this->statusBar(), SLOT(showMessage(QString)));



}

MainWindow::~MainWindow()
{
    //delete ui;
}
