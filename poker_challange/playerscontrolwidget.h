#ifndef PLAYERSCONTROLWIDGET_H
#define PLAYERSCONTROLWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include <vector>

#include "playerwidget.h"

namespace TexasHoldemView {
class PlayersControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayersControlWidget(QWidget *parent = 0);
    ~PlayersControlWidget();
    void setNOfPlayer(int n);
    void clearPlayers();
    void setPlayerBet(int i, int value) {_players[i]->setBet(value);}
    void setPalyerActive(int i, bool active) {
        _players[i]->setActivePlayer(active);
    }
    void setPlayerTextDecesion(int i,QString decesion) {_players[i]->setDecesion(decesion);}
    void setPossibleChoices(const QStringList &list);
    void inactivatePlayer() {setPalyerActive(_activePlayer,false);}

    void setActivePlayer(int index);
    void changeActivePlayer(int index);

    QString getActivePlayerDecesion() {return _players[_activePlayer]->getDesecition();}
    int getActivePlayerBet() {return _players[_activePlayer]->getBet();}

private:
    QGridLayout *_gridLayout;
    std::vector<PlayerWidget*> _players;

    int _activePlayer;

    static int SUBDIVISION;
};
}



#endif // PLAYERSCONTROLWIDGET_H
