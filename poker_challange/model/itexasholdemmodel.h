#ifndef ITEXASHOLDEMMODEL
#define ITEXASHOLDEMMODEL

#include <QObject>
#include "holdemtypes.h"
#include "card.h"
#include <list>
#include "player.h"
namespace Model
{

/*
 * Interface for buisness logic.
 */
class ITexasHoldemModel : public QObject
{
    Q_OBJECT
public:

    explicit ITexasHoldemModel(QObject *parent = 0) : QObject(parent) {}
    virtual ~ITexasHoldemModel() {}

    virtual void startGame(int players_, int smallBlindBet_, int bigBlindBet_,int playerNumber_, std::pair<Card, Card> hand_) = 0;
    virtual void stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet) = 0;
    virtual void startRound() = 0;
    virtual void addCommunityCards(const std::list<Card>& cards) = 0;
    virtual void setNOfPlayers(int n) = 0;
    virtual void setWorkerThreadNumber(int n) = 0;
signals:
    void activePlayerChanged(int newNumber);
    void newGameStarted(std::vector<Player> state);
    void endGame();
    void startBidding(int nextPlayer);
    void waitingCommunityCards();
    void selectCommunityCards(int from,int to);
    void roundStarted();
    void choiceOptionsChanged(bool beforeBet);
    void potChanged(int pot);
    void nOfActivePlayerChanged(int players);
    void yourBetChanged(int yourBet);
    void nextPlayerHint(TexasHoldem::desecition);
    void invalidState(QString message);

};

}
#endif // ITEXASHOLDEMMODEL

