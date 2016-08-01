#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "handevaluator.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    _evalator = new HandEvaluator();
    _possEvalator = new PossibleTableEvaluator();
}

void TexasHoldemModel::stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet)
{
    //begin hand..
    //next round..

    _playersState[(size_t)_nextPlayerr].lastDesecition = activePlayerDecesion;
    _playersState[(size_t)_nextPlayerr].bet = activePlayerBet;
    _nextPlayerr = (_nextPlayerr + 1) % _gameState.getNOfActivePlayers();
    emit activePlayerChanged(_nextPlayerr);

}

void TexasHoldemModel::startGame(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_)
{
    assert(players_ >= 2 && players_ < 24);

    _tableSumMoney = 0;
    _tableSumMoney += smallBlindBet_ + bigBlindBet_;

    setNOfPlayers(players_);

    minimumBet = bigBlindBet_;

    playerNumber = playerNumber_;

    _beforeBet = false;

    _playersState.resize(players_);
    _playersState[(size_t) (playerNumber - 1)].you = true;
    _playersState[0].bet = smallBlindBet_;
    _playersState[0].lastDesecition = TexasHoldem::bet;
    _playersState[1].bet = bigBlindBet_;
    _playersState[1].lastDesecition = TexasHoldem::bet;

    _nextPlayerr = 1;

    emit newGameStarted(_playersState,_nextPlayerr);
    emit waitingYourHand();
    //emit choiceOptionsChanged(_beforeBet);
}


TexasHoldemModel::~TexasHoldemModel()
{
    delete _evalator;
    delete _possEvalator;
}

TexasHoldem::desecition TexasHoldemModel::evaluate()
{

    _gameState.init();
    size_t size = _gameState.getCommunityCards().size();
    double winChance;
    if(size > 0)
    {
        double currentHandValue = _evalator->evaluate_hand(_gameState.getHiddenCards(),_gameState.getCommunityCards(),
                                   _gameState.getYourHand(),_gameState.getNOfActivePlayers());
        if(size < 5)
        {
            _possEvalator->setPair(_gameState.getYourHand());
            _possEvalator->setUnknownCards(_gameState.getHiddenCards());
            _possEvalator->setCommunityCards(_gameState.getCommunityCards());
            _possEvalator->setNOfPlayers(_gameState.getNOfActivePlayers());
            _possEvalator->evalauteChance();
            double chance = _possEvalator->getChance();
            if(size == 3)
            {
                winChance = 1 - ((1 - currentHandValue) * (1-chance)*(1-chance));
            }
            else if(size == 4)
            {
                winChance =  1 - (1 - currentHandValue)*(1 - chance);
            }

        }
        else
        {
            winChance = currentHandValue;
        }

    }
    else
    {
        double pair_value = _evalator->evaluate_pair(_gameState.getYourHand(),_gameState.getHiddenCards());
    }

    double expectedMoney = winChance*_gameState.getPot();

    if(expectedMoney < _gameState.getYourBet())
        return TexasHoldem::fold;
    else if( expectedMoney < _gameState.getYourBet()*2)
        return TexasHoldem::call;
    else
        return TexasHoldem::raise;



}

TexasHoldem::desecition TexasHoldemModel::evaluateChance(double c)
{
    if(c < 0.1)
        return TexasHoldem::fold;
    else if(c < 0.5)
        return TexasHoldem::call;
    else
        return TexasHoldem::raise;

}
