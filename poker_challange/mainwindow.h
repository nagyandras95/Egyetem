#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include "gamewidget.h"
#include "model/itexasholdemmodel.h"
#include "modelviewmatching.h"
#include "decesionmatcher.h"

namespace TexasHoldemView
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void initActions();
    void startingNewGame();
    void modelWitingCommunityCards();
    void modelStartingRound();
    void setWorkerThreadNumber();
    void showHint(TexasHoldem::desecition decesion);
    void newGameStarted();

private:

    void initDecesionMatching();

    QAction* _startAction;
    QAction* _threadConfigureAction;
    QAction* _exitAction;
    QAction* _nextAction;
    QAction* _startRoundAction;


    QMenu* _gameMenu; // játékmenü
    QMenu* _controlMenu;
    QMenu* _infoMenu;

    TexasHoldemView::GameWidget* _gameWidget;
    Model::ITexasHoldemModel* _model;

    TexasHoldemView::ThreadNumberSetDialog* _threadSetter;

    ModelViewMatching<TexasHoldem::desecition,DecesionMatcher>* _decesionMatcher;


};

}


#endif // MAINWINDOW_H
