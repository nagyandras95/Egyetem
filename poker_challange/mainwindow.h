#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include "gamewidget.h"
#include "model/texasholdemmodel.h"

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
    void showHint(TexasHoldem::desecition decesion) {return _decesationMatching[decesion]; }

private:

    void initDecesionMatching();

    QAction* _startAction;
    QAction* _threadConfigureAction;
    QAction* _exitAction; // kilépés akció
    QAction* _nextAction;
    QAction* _startRoundAction;


    QMenu* _gameMenu; // játékmenü
    QMenu* _controlMenu;
    QMenu* _infoMenu;

    TexasHoldemView::GameWidget* _gameWidget;
    TexasHoldemModel* _model;

    TexasHoldemView::ThreadNumberSetDialog* _threadSetter;

    std::map<TexasHoldem::desecition,QString> _decesationMatching;



};

}


#endif // MAINWINDOW_H
