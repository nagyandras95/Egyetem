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
    PlayerRoundState& currentPlayerState =  _playersState[(size_t)_currentPlayer];

    bool error = false;
    QString message;
    if(activePlayerBet < _minimumBet || activePlayerBet < currentPlayerState.bet)
    {
        error = true;
        message = "Error: The bet must be at least the minimum bet amount!";

    }

    if(activePlayerDecesion == TexasHoldem::raise && activePlayerBet <= currentPlayerState.bet)
    {
        error = true;
        message = "Error: The raised money must be more then the current money!";
    }

    if(activePlayerDecesion == TexasHoldem::none)
    {
        error = true;
        message = "Error: You must make a decesion!";
    }

    if(error)
    {
        emit invalidState(message);
        return;
    }

    if(activePlayerDecesion == TexasHoldem::bet)
    {
        _beforeBet = false;
        emit choiceOptionsChanged(_beforeBet);

    }

    if(activePlayerDecesion == TexasHoldem::raise)
    {
        if(_nOfRaises == 0)
        {
            _roundStarterPlayer = _currentPlayer;

        }
        _nOfRaises++;
    }
    else if(activePlayerDecesion == TexasHoldem::fold)
    {
        _nOfActivePlayers--;
    }

    _tableSumMoney += (activePlayerBet - currentPlayerState.bet);
    currentPlayerState.lastDesecition = activePlayerDecesion;
    currentPlayerState.bet = activePlayerBet;

    _currentPlayer = searchNextAtivePlayer();
    if(_currentPlayer == _roundStarterPlayer)
    {
         _beforeBet = true;
         int size = _gameState.getCommunityCards().size();
         if( size == 0)
         {
             emit selectCommunityCards(0,2);

         }
         else if(size == 3)
         {
             emit selectCommunityCards(3,3);
         }
         else if(size == 4)
         {
             emit selectCommunityCards(4,4);
         }

         emit choiceOptionsChanged(_beforeBet);
    }

    emit activePlayerChanged(_currentPlayer);


    if(_currentPlayer == playerNumber)
    {
        //hint..
    }

}

void TexasHoldemModel::addCommunityCards(const std::list<card> &cards)
{
    for(card c : cards)
    {
        _gameState.addCommunityCard(c);
    }
    emit nextRoundStarted(_currentPlayer);
}

void TexasHoldemModel::startGame(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_)
{
    assert(players_ >= 2 && players_ < 24);

    _tableSumMoney = 0;
    _tableSumMoney += smallBlindBet_ + bigBlindBet_;
    _round = TexasHoldem::pre_flop;
    _nOfActivePlayers = players_;
    setNOfPlayers(players_);

    _minimumBet = bigBlindBet_;

    playerNumber = playerNumber_ - 1;

    _beforeBet = false;

    _playersState.resize(players_);
    _playersState[(size_t) (playerNumber - 1)].you = true;
    _playersState[0].bet = smallBlindBet_;
    _playersState[0].lastDesecition = TexasHoldem::bet;
    _playersState[1].bet = bigBlindBet_;
    _playersState[1].lastDesecition = TexasHoldem::bet;

    _currentPlayer = 1;
    _roundStarterPlayer = searchNextAtivePlayer();

    emit newGameStarted(_playersState,_currentPlayer);
    emit waitingYourHand();
    //emit choiceOptionsChanged(_beforeBet);
}

int TexasHoldemModel::searchNextAtivePlayer()
{
    int n = _gameState.getNOfActivePlayers();
    int next = (_currentPlayer + 1) % n;
    while(_playersState[next].lastDesecition == TexasHoldem::fold)
        next = (next + 1) % n;

    return next;
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
        winChance = _evalator->evaluate_pair(_gameState.getYourHand(),_gameState.getHiddenCards());
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
