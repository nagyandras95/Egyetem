#include "playerscontrolwidget.h"
#include <assert.h>

int PlayersControlWidget::SUBDIVISION = 8;

PlayersControlWidget::PlayersControlWidget(QWidget *parent) : QWidget(parent)
{
    _gridLayout = new QGridLayout;

    setLayout(_gridLayout);
}

void PlayersControlWidget::setNOfPlayer(int n)
{
    assert(n < 24 && n >= 2);
    _activePlayer = 0;
    for(int i = 0; i < (int)_players.size(); ++i)
    {
        _gridLayout->removeWidget(_players[i]);
        delete _players[i];
    }
    _players.clear();

    for(int i = 0; i < n; ++i)
    {
        _players.push_back(new PlayerWidget);
        _gridLayout->addWidget(_players[i],i/SUBDIVISION,i%SUBDIVISION);
    }
}

void PlayersControlWidget::setPossibleChoices(const QStringList& list)
{
    for(PlayerWidget* player: _players)
    {
        player->changeChoiceList(list);
    }
}

void PlayersControlWidget::setActivePlayer(int index)
{
    setPalyerActive(index,true);
    _activePlayer = index;
}

void PlayersControlWidget::changeActivePlayer(int index)
{
    inactivatePlayer();
    setActivePlayer(index);
}
