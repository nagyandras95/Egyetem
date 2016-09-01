#include "mainwindow.h"
#include "model/combination.h"
#include "model/card.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

namespace TexasHoldemView
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //setMinimumSize(400,400);
    setWindowTitle(trUtf8("Texas Hold'em Poker Assist"));

    _startAction = new QAction(trUtf8("Start"),this);
    _startAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    _startAction->setStatusTip(trUtf8("Start game simulating"));

    _threadConfigureAction = new QAction(trUtf8("Threads"),this);
    _threadConfigureAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    _threadConfigureAction->setStatusTip(trUtf8("Configure number of calculating threads."));

    _exitAction = new QAction(trUtf8("&Exit"), this);
    _exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    _exitAction->setStatusTip(trUtf8("Exiting from assistant"));

    _nextAction = new QAction(trUtf8("Next"),this);
    _nextAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    _nextAction->setStatusTip(trUtf8("Next player."));

    _startRoundAction = new QAction(trUtf8("Start round"),this);
    _startRoundAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    _startRoundAction->setStatusTip(trUtf8("Starting the next round"));

    _gameMenu = menuBar()->addMenu(trUtf8("&File"));

    _gameMenu->addAction(_threadConfigureAction);
    _gameMenu->addSeparator();
    _gameMenu->addAction(_exitAction);

    _controlMenu = menuBar()->addMenu(trUtf8("&Control"));
    _controlMenu->addAction(_startAction);
    _controlMenu->addAction(_startRoundAction);
    _controlMenu->addAction(_nextAction);

    _infoMenu = menuBar()->addMenu(trUtf8("&Info"));

    _model = new TexasHoldemModel(this);

    _gameWidget = new GameWidget(_model,this);
    _threadSetter = new ThreadNumberSetDialog(this);
    setCentralWidget(_gameWidget);

    connect(_nextAction,SIGNAL(triggered()),_gameWidget,SLOT(stepGame()));
    connect(_threadConfigureAction,SIGNAL(triggered()),_threadSetter,SLOT(show()));
    connect(_startAction,SIGNAL(triggered()),this, SLOT(startingNewGame()));
    connect(_exitAction,SIGNAL(triggered()),this,SLOT(close()));

    connect(_model,SIGNAL(newGameStarted(std::vector<Player>)),
            _gameWidget,SLOT(newGameStarted(std::vector<Player>)));
    connect(_model,SIGNAL(selectCommunityCards(int,int)),_gameWidget,SLOT(enableCommunityCardSelection(int,int)));
    connect(_model,SIGNAL(activePlayerChanged(int)),_gameWidget,SLOT(changeActivePlayer(int)));
    connect(_model,SIGNAL(choiceOptionsChanged(bool)),_gameWidget,SLOT(switchCoiceOption(bool)));
    connect(_model,SIGNAL(nOfActivePlayerChanged(int)),_gameWidget,SLOT(changeNofPlayers(int)));
    connect(_model,SIGNAL(potChanged(int)),_gameWidget,SLOT(changePot(int)));
    connect(_model,SIGNAL(yourBetChanged(int)),_gameWidget,SLOT(changeYourBet(int)));
    connect(_model,SIGNAL(nextPlayerHint()),_gameWidget,SLOT(getHint()));
    connect(_model,SIGNAL(endGame()),_gameWidget,SLOT(initSelections()));

    connect(_gameWidget, SIGNAL(hintAdded(QString)), this->statusBar(), SLOT(showMessage(QString)));
    connect(_model,SIGNAL(waitingCommunityCards()),this,SLOT(modelWitingCommunityCards()));
    connect(_model,SIGNAL(invalidState(QString)),this->statusBar(),SLOT(showMessage(QString)));
    connect(_model,SIGNAL(roundStarted()),this,SLOT(modelStartingRound()));
    connect(_model,SIGNAL(endGame()),this,SLOT(initActions()));

    connect(_threadSetter,SIGNAL(accepted()),this,SLOT(setWorkerThreadNumber()));
    connect(_threadSetter,SIGNAL(rejected()),_threadSetter,SLOT(close()));

    initActions();

}

MainWindow::~MainWindow()
{
    delete _model;
}

void MainWindow::initActions()
{
    _startAction->setEnabled(true);
    _startRoundAction->setEnabled(false);
    _nextAction->setEnabled(false);
}

void MainWindow::startingNewGame()
{
    _model->startGame(_gameWidget->getnOfPlayers(),_gameWidget->getSmallBlindBet(),
                      _gameWidget->getBigBlindBet(), _gameWidget->getYourNumber());
    _startAction->setEnabled(false);
    _startRoundAction->setEnabled(true);
    _gameWidget->givePairs();
}

void MainWindow::modelWitingCommunityCards()
{
    this->statusBar()->showMessage("Plase, give the community cards and click to Start round!");
    disconnect(_startRoundAction,SIGNAL(triggered()),_gameWidget,SLOT(givePairs()));
    connect(_startRoundAction,SIGNAL(triggered()), _gameWidget, SLOT(addActiveCommunityCards()));
    _startRoundAction->setEnabled(true);
    _nextAction->setEnabled(false);
}

void MainWindow::modelStartingRound()
{
    _nextAction->setEnabled(true);
    _startRoundAction->setEnabled(false);
}

void MainWindow::setWorkerThreadNumber()
{
    _model->setWorkerThreadNumber(_threadSetter->getNOfThreads());
}
}



