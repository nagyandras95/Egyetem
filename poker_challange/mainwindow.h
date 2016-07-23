#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <texasholdemmodel.h>
#include "gamewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:


    QAction* _newGameAction; // új játék akció
    QAction* _exitAction; // kilépés akció
    QAction* _configureAction; // beállítások akciója
    QAction* _hintAction;

    QMenu* _gameMenu; // játékmenü
    QMenu* _infoMenu;

    GameWidget* _gameWidget; // játékmezõ vezérlője


};

#endif // MAINWINDOW_H
