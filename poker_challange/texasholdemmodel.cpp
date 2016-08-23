#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "handevaluator.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    _evalator = new HandEvaluator();
    _possEvalator = new PossibleTableEvaluator();
}

TexasHoldemModel::~TexasHoldemModel()
{
    delete _evalator;
    delete _possEvalator;
}

void TexasHoldemModel::startGame(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_)
{
    assert(players_ >= 2 && players_ < 24);

    _tableSumMoney = smallBlindBet_ + bigBlindBet_;
    _round = TexasHoldem::pre_flop;
    _nOfActivePlayers = players_;
    nOfStartedPlayer = players_;
    setNOfPlayers(players_);

    _minimumBet = bigBlindBet_;

    playerNumber = playerNumber_ - 1;

    _beforeBet = false;

    _playersState.resize(players_);
    _playersState[0].bet = smallBlindBet_;
    _playersState[0].lastDesecition = TexasHoldem::bet;
    _playersState[1].bet = bigBlindBet_;
    _playersState[1].lastDesecition = TexasHoldem::bet;

    emit newGameStarted(_playersState);
    emit waitingYourHand();
}

void TexasHoldemModel::startRound()
{
    _nOfRaises = 0;
    _roundStarterPlayer = serachFirstActivePlayer();
    _currentPlayer = serachFirstActivePlayer();

    if(_round != TexasHoldem::pre_flop)
        _tableSumMoney = 0;

    emit activePlayerChanged(_roundStarterPlayer);
}

void TexasHoldemModel::stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet)
{
    Player& currentPlayerState =  _playersState[(size_t)_currentPlayer];

    std::pair<bool,QString> errorState = validateState(activePlayerDecesion,activePlayerBet,currentPlayerState);
    if(errorState.first)
    {
        emit invalidState(errorState.second);
        return;
    }


    if(activePlayerDecesion == TexasHoldem::bet)
    {
        _beforeBet = false;
        _minimumBet = activePlayerBet;
        emit choiceOptionsChanged(_beforeBet);

    }

    if(activePlayerDecesion == TexasHoldem::raise)
    {
        if(_nOfRaises == 0)
        {
            _roundStarterPlayer = _currentPlayer;

        }
        _nOfRaises++;
        _minimumBet = activePlayerBet;
    }
    else if(activePlayerDecesion == TexasHoldem::fold)
    {
        _nOfActivePlayers--;
        _gameState.decrementNOfActivePlayers();
        emit nOfActivePlayerChanged(_gameState.getNOfActivePlayers());

    }

    _tableSumMoney += (activePlayerBet - currentPlayerState.bet);
    if(_currentPlayer == playerNumber)
    {
        _gameState.addYourBet(activePlayerBet);
        emit yourBetChanged(_gameState.getYourBet());
    }

    currentPlayerState.lastDesecition = activePlayerDecesion;
    currentPlayerState.bet = activePlayerBet;




    if(searchNextAtivePlayer() == _roundStarterPlayer)
    {
         if(_round == TexasHoldem::river)
             emit endGame();

         _beforeBet = true;
         int size = _gameState.getCommunityCards().size();
         if(size < 5)
         {
             emit waitingCommunityCards();
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
         }
         _gameState.addPot(_tableSumMoney);
         nextRound();
         emit potChanged(_gameState.getPot());
         emit choiceOptionsChanged(_beforeBet);

    }
    else
    {
        _currentPlayer = searchNextAtivePlayer();
        emit activePlayerChanged(_currentPlayer);
    }




    if(_currentPlayer == playerNumber)
    {
        emit nextPlayerHint();
    }

}



void TexasHoldemModel::addCommunityCards(const std::list<card> &cards)
{
    for(card c : cards)
    {
        _gameState.addCommunityCard(c);
    }
    emit nextRoundStarted(_roundStarterPlayer);
}



int TexasHoldemModel::searchNextAtivePlayer()
{
     int n = nOfStartedPlayer;
     int next = (_currentPlayer + 1) % n;
     while(_playersState[next].lastDesecition == TexasHoldem::fold)
         next = (next + 1) % n;

     return next;
}



int TexasHoldemModel::serachFirstActivePlayer()
{
    int n = nOfStartedPlayer;
    int first = _round == TexasHoldem::pre_flop ? (2 % n) : 0;
    while(_playersState[first].lastDesecition == TexasHoldem::fold)
        first = (first + 1) % n;

    return first;

}




TexasHoldem::desecition TexasHoldemModel::evaluate()
{

    size_t size = _gameState.getCommunityCards().size();
    if(size > 0)
    {
        double currentHandValue = _evalator->evaluateHand(_gameState.getHiddenCards(),_gameState.getCommunityCards(),
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
                winChance = 1 - ((1-chance)*(1-chance));
            }
            else if(size == 4)
            {
                winChance = chance;
            }

        }
        else
        {
            winChance = currentHandValue;
        }

    }
    else
    {
        winChance = _evalator->evaluatePair(_gameState.getYourHand(),
                                            _gameState.getHiddenCards(),_gameState.getNOfActivePlayers());
        /*
         * In the pre-flop we does not have any investment
         * so the logic is very simple: only realy strong hand should be played.
        */
        if(winChance < 0.9)
        {
            if(playerNumber == 2 && _nOfRaises > 0 && winChance > 0.8 || playerNumber == 2 && _nOfRaises == 0)
                return TexasHoldem::call;
            else
                return TexasHoldem::fold;
        }
        else if(winChance > 0.98)
        {
            return TexasHoldem::raise;
        }
        else if(winChance > 0.95)
        {
            if(_nOfRaises == 0)
                return TexasHoldem::raise;
            else
                return TexasHoldem::call;
        }
        else
        {
            if(_nOfRaises == 0)
                return TexasHoldem::call;
            else
                return TexasHoldem::fold;
        }

    }


    double expectedMoney = winChance*(_gameState.getPot() +  _tableSumMoney +
                             (_minimumBet - _playersState[playerNumber - 1].bet));

    if(!_beforeBet)
    {
        /*
         * If the expected money less then the already invested and should be
         * invested money in tis situtaion
         * it does not worth to call it.
        */
        if(expectedMoney < (_gameState.getYourBet() + (_minimumBet - _playersState[playerNumber - 1].bet)))
        {
            return TexasHoldem::fold;
        }
        else
        {
            /*
             * We should consider what the optimal decesion is: call or raise.
             * Our gone to maximase our profit, for that we should consider our and opponents chances..
            */

            int afterRisePot;
            int afterRaiseInvest;
            int raiseAmount = _round == TexasHoldem::flop ? flopRaise : afterFlopRaise;
            if(_round == TexasHoldem::flop)
            {
                afterRisePot = _gameState.getPot() +  _tableSumMoney +
                         (_minimumBet + raiseAmount - _playersState[playerNumber - 1].bet);
                afterRaiseInvest = _gameState.getYourBet() + (_minimumBet + raiseAmount - _playersState[playerNumber - 1].bet);
            }

            expectedMoney = winChance*(afterRisePot);
            if(expectedMoney < (_gameState.getYourBet() + afterRaiseInvest))
            {
                return TexasHoldem::call;
            }
            else
            {
                int raiseAmount = _round == TexasHoldem::flop ? flopRaise : afterFlopRaise;

                int sumRaisePlusMoney = 0;
                int sumNoRaisePlusMoney = 0;
                for(Player player: _playersState)
                {
                    if(analyizePlayer(player,_minimumBet))
                    {
                        sumNoRaisePlusMoney += _minimumBet;
                    }
                    _playersState[playerNumber-1].raisePower++;
                    if(analyizePlayer(player,_minimumBet + raiseAmount))
                    {
                        sumRaisePlusMoney += _minimumBet + raiseAmount;
                    }
                    _playersState[playerNumber-1].raisePower--;

                    if(sumNoRaisePlusMoney > sumRaisePlusMoney)
                    {
                        return TexasHoldem::call;
                    }
                    else
                    {
                        return TexasHoldem::raise;
                    }

                }
            }



        }

    }
    else
    {
        if(winChance*(totalPot()) < _gameState.getYourBet())
        {
            return TexasHoldem::check;
        }
        else
        {

        }

    }

}


bool TexasHoldemModel::analyizePlayer(Player player,int toCallAmount)
{

    //first case

    //that's mean the player needs at last as many chance as invest rate
    double investRate = (double) (player.getTotalBet() + (toCallAmount - player.bet)) /
                        (double) (totalPot() + (toCallAmount - player.bet));

    double chance = (1 - winChance) + 0.1*
            (player.raisePower - _playersState[playerNumber-1].raisePower);

    if(chance > investRate)
        return true;
    else
        return false;



}

void TexasHoldemModel::nextRound()
{
    switch(_round)
    {
        case TexasHoldem::pre_flop:
            _round = TexasHoldem::flop; break;
        case TexasHoldem::flop:
            _round = TexasHoldem::turn; break;
        case TexasHoldem::turn:
            _round = TexasHoldem::river; break;
        default:
            _round = TexasHoldem::pre_flop;
    }
}

std::pair<bool,QString> TexasHoldemModel::validateState(TexasHoldem::desecition activePlayerDecesion,
int activePlayerBet, const Player& activePlayerState)
{
    std::pair<bool,QString> errorState(false,"");
    if((activePlayerBet < _minimumBet || activePlayerBet < activePlayerState.bet) && activePlayerDecesion == TexasHoldem::call)
    {
        errorState.first  = true;
        errorState.second = "Error: The bet must be at least the minimum bet amount!";

    }

    if(activePlayerDecesion == TexasHoldem::raise && activePlayerBet <= activePlayerState.bet)
    {
        errorState.first = true;
        errorState.second = "Error: The raised money must be more then the current money!";
    }

    if(activePlayerDecesion == TexasHoldem::none)
    {
        errorState.first  = true;
        errorState.second = "Error: You must make a decesion!";
    }

    return errorState;

}
