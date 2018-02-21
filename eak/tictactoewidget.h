#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>

class TicTacToeWidget : public QWidget // játékot megjelenítő ablak
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = 0);

private slots:
    void buttonClicked(); // táblagombra kattintás esménykezelője
    void newGameButtonClicked(); // új játék gombra kattintás eseménykezelője

private:
    void generateTable(); // tábla létrehozása

    QChar _currentPlayerSymbol; // aktuális játékosszimbólum
    QGridLayout* _tableLayout;
    QVBoxLayout* _mainLayout;
    QPushButton* _newGameButton; // új játék gombja
    QVector<QVector<QPushButton*> > _gameTableButtons; // gombtábla
};

#endif // TICTACTOEWIDGET_H
