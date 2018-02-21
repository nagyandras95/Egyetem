#include "tictactoewidget.h"
#include <QMessageBox>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 400);
    setBaseSize(400,400);
    setWindowTitle(tr("Tic-Tac-Toe"));

    _newGameButton = new QPushButton(trUtf8("Új játék")); // új játék gomb
    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));

    _mainLayout = new QVBoxLayout(); // vertikális elhelyezkedés a teljes felületnek
    _mainLayout->addWidget(_newGameButton);

    _tableLayout = new QGridLayout(); // rácsos elhelyezkedés a játékmezőnek
    _mainLayout->addLayout(_tableLayout);
    generateTable();

    setLayout(_mainLayout);

    _currentPlayerSymbol = 'X'; // kezdő játékos
}

void TicTacToeWidget::generateTable()
{
    _gameTableButtons.resize(3);

    for (int i = 0; i < 3; ++i)
    {
        _gameTableButtons[i].resize(3);
        for (int j = 0; j < 3; ++j)
        {
            _gameTableButtons[i][j]= new QPushButton(this);
            _gameTableButtons[i][j]->setFont(QFont("Times New Roman", 100, QFont::Bold));
            _gameTableButtons[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            _tableLayout->addWidget(_gameTableButtons[i][j], i, j); // gombok felvétele az elhelyezésbe

            connect(_gameTableButtons[i][j], SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }
}


void TicTacToeWidget::buttonClicked()
{
    // lekérjük az esemény küldőjét
    QPushButton* senderButton = dynamic_cast <QPushButton*> (sender());
    int location = _tableLayout->indexOf(senderButton);

    int x = location / 3; // a gomb rácson belüli pozíciója megadja a koordinátákat
    int y = location % 3;

    _gameTableButtons[x][y]->setText(_currentPlayerSymbol); // megjelenítés a gombon
    _gameTableButtons[x][y]->setEnabled(false);

    if (_currentPlayerSymbol == 'X') // váltjuk a játékost
        _currentPlayerSymbol = '0';
    else
        _currentPlayerSymbol = 'X';

    // ellenőrizzük, hogy vége van-e a játéknak
    QString won = "";

    // ellenőrzések a szimbólumra
    for (int i = 0; i < 3; ++i)
    {
        if (_gameTableButtons[i][0]->text() != "" && _gameTableButtons[i][0]->text() == _gameTableButtons[i][1]->text() && _gameTableButtons[i][1]->text() == _gameTableButtons[i][2]->text())
            won = _gameTableButtons[i][0]->text();
    }
    for (int i = 0; i < 3; ++i)
    {
        if (_gameTableButtons[0][i]->text() != "" && _gameTableButtons[0][i]->text() == _gameTableButtons[1][i]->text() && _gameTableButtons[1][i]->text() == _gameTableButtons[2][i]->text())
            won = _gameTableButtons[0][i]->text();
    }
    if (_gameTableButtons[0][0]->text() != "" && _gameTableButtons[0][0]->text() == _gameTableButtons[1][1]->text() && _gameTableButtons[1][1]->text() == _gameTableButtons[2][2]->text())
        won = _gameTableButtons[0][0]->text();
    if (_gameTableButtons[0][2]->text() != "" && _gameTableButtons[0][2]->text() == _gameTableButtons[1][1]->text() && _gameTableButtons[1][1]->text() == _gameTableButtons[2][0]->text())
        won = _gameTableButtons[0][2]->text();

    if (won == "X") // az eredmény függvényében jelenítjük meg a győztest
    {
        // előugró ablakban kiírjuk az üzenetet, majd új játékot kezdünk
        QMessageBox::information(this, trUtf8("Játék vége!"), trUtf8("Az X nyerte a játékot!"));
        newGameButtonClicked();
    }
    else if (won == "0")
    {
        QMessageBox::information(this, trUtf8("Játék vége!"), trUtf8("A O nyerte a játékot!"));
        newGameButtonClicked();
    }

    // ellenőrzés a játéktábla kitöltöttségére
    int numberOfChars = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (_gameTableButtons[i][j]->text() != "")
                numberOfChars++;
        }
    }

    if (numberOfChars == 9)
    {
        QMessageBox::information(this, trUtf8("Játék vége!"), trUtf8("A játék döntetlen lett!"));
        newGameButtonClicked();
    }
}

void TicTacToeWidget::newGameButtonClicked()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            _gameTableButtons[i][j]->setText(""); // a szöveget töröljük
            _gameTableButtons[i][j]->setEnabled(true); // bekapcsoljuk a gombot
        }

    _currentPlayerSymbol = 'X';
}
