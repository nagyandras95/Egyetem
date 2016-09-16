#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <vector>
#include <assert.h>
#include "ihandevaluator.h"
#include "card.h"
#include "gamingtableconfiguration.h"
#include "possibletableevaluator.h"
#include "player.h"
#include "possiblestate.h"
#include "strageist.h"
#include "itexasholdemmodel.h"

namespace Model
{
class TexasHoldemModel : public ITexasHoldemModel
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    virtual ~TexasHoldemModel();

    virtual void startGame(int players_, int smallBlindBet_, int bigBlindBet_,
                   int playerNumber_, std::pair<Card, Card> hand_);
    virtual void stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet);
    virtual void startRound();
    virtual void addCommunityCards(const std::list<Card>& cards);
    virtual void setNOfPlayers(int n) {_gameState.setNOfActivePlayers(n);}
    virtual void setWorkerThreadNumber(int n) {_strategist.setNOfWorkerThreads(n);}

private:


    std::pair<bool, QString> validateStepState(TexasHoldem::desecition, int activePlayerBet);
    std::pair<bool, QString> validateStartingState(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_,std::pair<Model::Card,Model::Card> hand_);
    bool stateNotContainsCards(const std::list<Card>&);


    GamingTableConfiguration _gameState;
    Strageist _strategist;
    bool _validState;


};
}
#endif // TEXASHOLDEMMODEL_H
