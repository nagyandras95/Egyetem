#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "handevaluator.h"
#include <queue>

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
    assert(players_ >= 2 && players_ < 11);

    _gameState.init();
    for(Player& player: _playersState)
    {
        player.allBet = 0;
    }
    _gameState.initTableSumMoney();
    _gameState.addTableMoney(smallBlindBet_ + bigBlindBet_);
    _gameState.setNOfActivePlayers(players_);
    _gameState.initNofStartedPlayer(players_);
    _round = TexasHoldem::pre_flop;

    _minimumBet = bigBlindBet_;

    flopRaise = bigBlindBet_;
    afterFlopRaise = bigBlindBet_*2;

    _playerPosition = playerNumber_ - 1;

    _beforeBet = false;

    _playersState.resize(players_);
    _playersState[0].bet = smallBlindBet_;
     _playersState[0].allBet = smallBlindBet_;
    _playersState[0].lastDesecition = TexasHoldem::bet;
    _playersState[1].bet = bigBlindBet_;
    _playersState[1].allBet = bigBlindBet_;
    _playersState[1].lastDesecition = TexasHoldem::bet;

    if(_playerPosition == 0)
        _gameState.addYourBet(smallBlindBet_);
    else if(_playerPosition == 1)
        _gameState.addYourBet(bigBlindBet_);

    emit newGameStarted(_playersState);
}

void TexasHoldemModel::startRound()
{
    _gameState.initRaises();
    _gameState.initCalls();
    _roundStarterPlayer = serachFirstActivePlayer();
    _currentPlayer = serachFirstActivePlayer();

    if(_round != TexasHoldem::pre_flop)
    {
        _gameState.initTableSumMoney();
        for(Player& player: _playersState)
        {
            player.bet = 0;
        }
    }
    emit roundStarted();
    emit activePlayerChanged(_roundStarterPlayer);
    if(_roundStarterPlayer == _playerPosition)
    {
        emit nextPlayerHint(evaluate());
    }
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

    if(activePlayerDecesion == TexasHoldem::raise)
    {
        if(_gameState.getRaises() == 0)
        {
            _roundStarterPlayer = _currentPlayer;

        }
        _gameState.incrementRaises();
        _minimumBet = activePlayerBet;
    }
    else if(activePlayerDecesion == TexasHoldem::bet)
    {
        _beforeBet = false;
        _minimumBet = activePlayerBet;
        _roundStarterPlayer = _currentPlayer;

        emit choiceOptionsChanged(_beforeBet);
    }
    else if(activePlayerDecesion == TexasHoldem::fold)
    {
        _gameState.decrementNOfActivePlayers();
        emit nOfActivePlayerChanged(_gameState.getNOfActivePlayers());
        if(_currentPlayer == _playerPosition)
        {
            emit endGame();
            return;
        }

    }


    if(activePlayerDecesion != TexasHoldem::fold || activePlayerDecesion != TexasHoldem::check)
    {
        _gameState.addTableMoney((activePlayerBet - currentPlayerState.bet));
        _gameState.incrementCalls();
        _playersState[_currentPlayer].allBet = activePlayerBet - currentPlayerState.bet;
    }

    if(_currentPlayer == _playerPosition)
    {
        _gameState.addYourBet(activePlayerBet - currentPlayerState.bet);
        emit yourBetChanged(_gameState.getYourBet());
    }

    currentPlayerState.lastDesecition = activePlayerDecesion;
    currentPlayerState.bet = activePlayerBet;

    if(searchNextAtivePlayer(_currentPlayer) == _roundStarterPlayer)
    {
        if(_round == TexasHoldem::river)
        {
            emit endGame();
        }
        else
        {
            _beforeBet = true;
        }
        if(_round != TexasHoldem::river)
        {
            emit waitingCommunityCards();
            if( _round == TexasHoldem::pre_flop)
            {
                emit selectCommunityCards(0,2);

            }
            else if(_round == TexasHoldem::flop)
            {
                emit selectCommunityCards(3,3);
            }
            else if(_round == TexasHoldem::turn)
            {
                emit selectCommunityCards(4,4);
            }

            _gameState.addTableToPot();
            nextRound();
            emit potChanged(_gameState.getPot());
            emit choiceOptionsChanged(_beforeBet);
        }
        return;

    }
    else
    {
        _currentPlayer = searchNextAtivePlayer(_currentPlayer);
        emit activePlayerChanged(_currentPlayer);
    }


    if(_currentPlayer == _playerPosition)
    {
        emit nextPlayerHint(evaluate());
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



int TexasHoldemModel::searchNextAtivePlayer(int current)
{
    int n = _gameState.getNofStarterPlayer();
    int next = (current + 1) % n;
    while(_playersState[next].lastDesecition == TexasHoldem::fold)
        next = (next + 1) % n;

    return next;
}



int TexasHoldemModel::serachFirstActivePlayer()
{
    int n = _gameState.getNofStarterPlayer();
    int first = _round == TexasHoldem::pre_flop ? (2 % n) : 0;
    while(_playersState[first].lastDesecition == TexasHoldem::fold)
        first = (first + 1) % n;

    return first;

}

int TexasHoldemModel::positionDiffRelatedToStarter(int pos)
{
    int count = 0;
    int starter = pos;
    while(starter != _roundStarterPlayer)
    {
        count++;
        starter = searchNextAtivePlayer(starter);
    }

    return count;
}




TexasHoldem::desecition TexasHoldemModel::evaluate()
{
    if(_round == TexasHoldem::pre_flop)
    {
        return preFlopStaregy();
    }
    else if(_round == TexasHoldem::flop)
    {
        flopWinChance();
    }
    else if(_round == TexasHoldem::turn)
    {
        turnWinChance();
    }
    else //river
    {
        riverWinChance();
    }



    if(!_beforeBet)
    {
        return afterBetStaregy();

    }
    else
    {
        return beforeBetStartegy();

    }

}

TexasHoldem::desecition TexasHoldemModel::preFlopStaregy()
{
    winChance = _evalator->evaluatePair(_gameState.getYourHand(),
                                        _gameState.getHiddenCards(),_gameState.getNOfActivePlayers());
    /*
                             * In the pre-flop we does not have any investment
                             * so the logic is very simple: only realy strong hand should be played.
                            */
    if(winChance < 0.9)
    {
        if((_playerPosition == 1 && _nOfRaises > 0 && winChance > 0.8) || (_playerPosition == 1 && _nOfRaises == 0))
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

TexasHoldem::desecition TexasHoldemModel::beforeBetStartegy()
{
    if(winChance*(_gameState.getTotalPot()) < _gameState.getYourBet())
    {
        return TexasHoldem::check;
    }
    else
    {
        return TexasHoldem::bet;
    }
}

TexasHoldem::desecition TexasHoldemModel::afterBetStaregy()
{
    double expectedMoney = winChance*(_gameState.getTotalPot() + (_minimumBet - _playersState[_playerPosition].bet));
    /*
                             * If the expected money less then the already invested and should be
                             * invested money in tis situtaion
                             * it does not worth to call it.
                            */
    if(expectedMoney < (_gameState.getYourBet() + (_minimumBet - _playersState[_playerPosition].bet)))
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
            afterRisePot = _gameState.getTotalPot() + (_minimumBet + raiseAmount - _playersState[_playerPosition].bet);
            afterRaiseInvest = _gameState.getYourBet() + (_minimumBet + raiseAmount - _playersState[_playerPosition].bet);
        }

        expectedMoney = winChance*(afterRisePot);
        if(expectedMoney < afterRaiseInvest)
        {
            return TexasHoldem::call;
        }
        else if(_gameState.getRaises() == 0)
        {
            return TexasHoldem::raise;
        }
        else
        {
            return analyzeBestOption();
        }

    }
}

TexasHoldem::desecition TexasHoldemModel::analyzeBestOption()
{
    PossibaleState myState(_gameState.getTotalPot(),_playerPosition,_minimumBet,_gameState.getRaises(),_gameState.getCalls(),1);
    std::list<PossibaleState> startingStates = getStateChildren(myState);
    PossibaleState callState = startingStates.front();
    PossibaleState raiseState = startingStates.back();

    if(analyzeBranch(callState) < analyzeBranch(raiseState))
    {
        return TexasHoldem::raise;
    }
    else
    {
        return TexasHoldem::call;
    }


}

double TexasHoldemModel::calculateOutChance()
{
    _possEvalator->setPair(_gameState.getYourHand());
    _possEvalator->setUnknownCards(_gameState.getHiddenCards());
    _possEvalator->setCommunityCards(_gameState.getCommunityCards());
    _possEvalator->setNOfPlayers(_gameState.getNOfActivePlayers());
    _possEvalator->evalauteChance();
    return _possEvalator->getChance();
}

void TexasHoldemModel::flopWinChance()
{
    double chance = calculateOutChance();
    winChance = 1 - (1-chance)*(1-chance);
}

void TexasHoldemModel::turnWinChance()
{
    winChance = calculateOutChance();

}

void TexasHoldemModel::riverWinChance()
{
    winChance = _evalator->evaluateHand(_gameState.getHiddenCards(),_gameState.getCommunityCards(),
                                        _gameState.getYourHand(),_gameState.getNOfActivePlayers());
}

std::list<PossibaleState> TexasHoldemModel::getStateChildren(PossibaleState state)
{
    std::list<PossibaleState> childen;


    int next = searchNextAtivePlayer(state.playerPosition);
    int raiseAmount = _round == TexasHoldem::flop ? flopRaise : afterFlopRaise;
    if(state.playerPosition != _roundStarterPlayer)
    {
        int callInvest = getAdditionInvest(state.playerPosition,state.minimumCall,TexasHoldem::call);
        int raiseInvest = getAdditionInvest(state.playerPosition,state.minimumCall,TexasHoldem::raise);

        int callPot = state.pot + callInvest;
        int raisePot = state.pot + raiseInvest;
        double callChance = 1 - ((double) (_playersState[state.playerPosition].allBet + callInvest) / callPot) -
                ((double) 0.01*_gameState.getCalls() + 0.05*_gameState.getRaises());
        double foldChance = 1 - callChance;
        double raiseChance = 1 - ((double) (_playersState[state.playerPosition].allBet + raiseInvest) / raisePot) -
                ((double) 0.02*_gameState.getCalls() + 0.1* (_gameState.getRaises() - positionDiffRelatedToStarter(state.playerPosition)));
        if(state.playerPosition == _playerPosition)
        {
            callChance = 1;
            raiseChance = 1;
        }
        childen.push_back(PossibaleState(callPot,next,state.minimumCall,state.nOfRaises,state.nOfCalls + 1, state.chance*callChance));
        if(next != _roundStarterPlayer)
        {
            childen.push_back(PossibaleState(raisePot,next,state.minimumCall + raiseAmount,state.nOfRaises + 1,state.nOfCalls,state.chance*raiseChance));
        }

        if(state.playerPosition != _playerPosition)
        {
            childen.push_back(PossibaleState(state.pot,next,state.minimumCall,state.nOfRaises,state.nOfCalls,state.chance*foldChance));
        }
    }

    return childen;


}

double TexasHoldemModel::analyzeBranch(const PossibaleState &root)
{
    double expectedMoney = 0;
    int countLeaf = 0;
    std::queue<PossibaleState,std::list<PossibaleState> > stateQueue(getStateChildren(root));
    while(!stateQueue.empty())
    {
        PossibaleState state = stateQueue.front();
        stateQueue.pop();
        std::list<PossibaleState> children = getStateChildren(state);
        for(PossibaleState child : children)
        {
            stateQueue.push(child);
        }
        if(children.empty())
        {
            expectedMoney += state.chance * state.pot;
            countLeaf++;
        }
    }
    return expectedMoney / countLeaf;
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
    case TexasHoldem::river :
        emit endGame();
        break;
    default:
        _round = TexasHoldem::pre_flop;
    }
}

int TexasHoldemModel::getAdditionInvest(int playerPosition, int minCall, TexasHoldem::desecition dec)
{
    if(dec == TexasHoldem::call)
    {
        return minCall - _playersState[playerPosition].bet;
    }
    else // TexasHoldem::raise
    {
        int raiseAmount = _round == TexasHoldem::flop ? flopRaise : afterFlopRaise;
        return minCall + raiseAmount - _playersState[playerPosition].bet;
    }
}



std::pair<bool,QString> TexasHoldemModel::validateState(TexasHoldem::desecition activePlayerDecesion,                                                        int activePlayerBet, const Player& activePlayerState)
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


