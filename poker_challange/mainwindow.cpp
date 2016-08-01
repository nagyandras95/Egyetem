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

    _startAction = new QAction(trUtf8("Start"),this);
    _startAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    _startAction->setStatusTip(trUtf8("Start game simulating"));

    _hintAction = new QAction(trUtf8("Hint"),this);
    _hintAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    _hintAction->setStatusTip(trUtf8("Adding the next hint"));

    _threadConfigureAction = new QAction(trUtf8("Threads"),this);
    _threadConfigureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    _threadConfigureAction->setStatusTip(trUtf8("Configure number of calculating threads."));

    _exitAction = new QAction(trUtf8("&Exit"), this);
    _exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _exitAction->setStatusTip(trUtf8("Exiting from assistant"));

    _nextAction = new QAction(trUtf8("Next"),this);
    _nextAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    _nextAction->setStatusTip(trUtf8("Next player."));

    _gameMenu = menuBar()->addMenu(trUtf8("&Game"));
    _gameMenu->addAction(_startAction);
    _gameMenu->addAction(_hintAction);
    _gameMenu->addAction(_threadConfigureAction);
    _gameMenu->addSeparator();
    _gameMenu->addAction(_exitAction);

    _controlMenu = menuBar()->addMenu(trUtf8("Control"));
    _controlMenu->addAction(_nextAction);

    _infoMenu = menuBar()->addMenu(trUtf8("&Info"));

    _model = new TexasHoldemModel(this);

    _gameWidget = new GameWidget(_model,this);
    _threadSetter = new ThreadNumberSetDialog(this);
    setCentralWidget(_gameWidget);

    connect(_hintAction,SIGNAL(triggered()),_gameWidget,SLOT(getHint()));
    connect(_model,SIGNAL(newGameStarted(std::vector<PlayerRoundState>,int)),
            _gameWidget,SLOT(newGameStarted(std::vector<PlayerRoundState>,int)));
    connect(_model,SIGNAL(activePlayerChanged(int)),_gameWidget,SLOT(changeActivePlayer(int)));
    connect(_nextAction,SIGNAL(triggered()),_gameWidget,SLOT(stepGame()));
    connect(_startAction,SIGNAL(triggered()),this, SLOT(startingNewGame()));
    connect(_threadConfigureAction,SIGNAL(triggered()),_threadSetter,SLOT(show()));
    connect(_model,SIGNAL(waitingYourHand()),this,SLOT(modelWaitingYourHand()));
    connect(_gameWidget, SIGNAL(hintAdded(QString)), this->statusBar(), SLOT(showMessage(QString)));




}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::startingNewGame()
{
    _model->startGame(_gameWidget->getnOfPlayers(),_gameWidget->getSmallBlindBet(),
                      _gameWidget->getBigBlindBet(), _gameWidget->getYourNumber());
}

void MainWindow::modelWaitingYourHand()
{
    this->statusBar()->showMessage("Plase, give your hand and click to Next!");
}

