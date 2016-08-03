#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <texasholdemmodel.h>
#include "gamewidget.h"
#include "texasholdemmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void startingNewGame();
    void modelWaitingYourHand();
    void modelWitingCommunityCards();
private:

    QAction* _startAction;
    QAction* _hintAction;
    QAction* _threadConfigureAction;
    QAction* _exitAction; // kilépés akció
    QAction* _nextAction;
    QAction* _startRoundAction;


    QMenu* _gameMenu; // játékmenü
    QMenu* _controlMenu;
    QMenu* _infoMenu;

    GameWidget* _gameWidget;
    TexasHoldemModel* _model;

    ThreadNumberSetDialog* _threadSetter;



};

#endif // MAINWINDOW_H
