#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "handevaluator.h"
#include <queue>

namespace Model
{
TexasHoldemModel::TexasHoldemModel(QObject *parent) : ITexasHoldemModel(parent), _strategist(_gameState), _validState(true) {}

TexasHoldemModel::~TexasHoldemModel() {}

void TexasHoldemModel::startGame(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_,
                                 std::pair<Model::Card,Model::Card> hand_)
{
    assert(players_ >= 2 && players_ < 11);
    std::pair<bool,QString> error = validateStartingState(players_,smallBlindBet_,bigBlindBet_,playerNumber_,hand_);
    if(error.first)
    {
        emit invalidState(error.second);
        return;
    }

    _gameState.init();
    _gameState.setYourHand(hand_.first,hand_.second);
    _gameState.initTableSumMoney();
    _gameState.addTableMoney(smallBlindBet_ + bigBlindBet_);
    _gameState.setNOfActivePlayers(players_);
    _gameState.initNofStartedPlayer(players_);
    _gameState.firstRound();
    _gameState.setMinimumBet(bigBlindBet_);
    _gameState.setPlayerPosition(playerNumber_ - 1);
    _gameState.setBigBlind(bigBlindBet_);
    _gameState.resizePlayerState(players_);

    _gameState.getPositionedPlayer(0).bet = smallBlindBet_;
    _gameState.getPositionedPlayer(0).allBet = smallBlindBet_;
    _gameState.getPositionedPlayer(0).lastDesecition = TexasHoldem::bet;
    _gameState.getPositionedPlayer(1).bet = bigBlindBet_;
    _gameState.getPositionedPlayer(1).allBet = bigBlindBet_;
    _gameState.getPositionedPlayer(1).lastDesecition = TexasHoldem::bet;

    if(_gameState.playerIsSmallBlind())
        _gameState.addYourBet(smallBlindBet_);
    else if(_gameState.playerIsBigBlind())
        _gameState.addYourBet(bigBlindBet_);

    emit newGameStarted(_gameState.getPlayersState());
    startRound();
}

void TexasHoldemModel::startRound()
{
    if(!_validState)
    {
        return;
    }

    _gameState.initRaises();
    _gameState.initCalls();
    _gameState.serachFirstActivePlayer();

    if(_gameState.getRound() != TexasHoldem::pre_flop)
    {
        _gameState.initTableSumMoney();
        _gameState.initPlayersBet();
    }
    emit roundStarted();
    emit activePlayerChanged(_gameState.getRoundStarter());
    if(_gameState.roundStarterIsThePlayer())
    {
        emit nextPlayerHint(_strategist.evaluate());
    }
}

void TexasHoldemModel::stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet)
{
    Player& currentPlayerState =  _gameState.getCurrentPlayerState();
    std::pair<bool,QString> errorState = validateStepState(activePlayerDecesion,activePlayerBet);
    if(errorState.first)
    {
        emit invalidState(errorState.second);
        return;
    }

    if(activePlayerDecesion == TexasHoldem::raise)
    {
        if(_gameState.getRaises() == 0)
        {
            _gameState.setRoundStarter(_gameState.getCurrentPlayer());

        }
        _gameState.incrementRaises();
        _gameState.setMinimumBet(activePlayerBet);
    }
    else if(activePlayerDecesion == TexasHoldem::bet)
    {
        _gameState.changeBeforeBet();
        _gameState.setMinimumBet(activePlayerBet);
        _gameState.setRoundStarter(_gameState.getCurrentPlayer());

        emit choiceOptionsChanged(_gameState.isBeforeBet());
    }
    else if(activePlayerDecesion == TexasHoldem::fold)
    {
        _gameState.decrementNOfActivePlayers();
        emit nOfActivePlayerChanged(_gameState.getNOfActivePlayers());
        if(_gameState.currentPlayerIsThePlayer())
        {
            emit endGame();
            return;
        }

    }


    if(activePlayerDecesion != TexasHoldem::fold && activePlayerDecesion != TexasHoldem::check)
    {
        _gameState.addTableMoney((activePlayerBet - currentPlayerState.bet));
        _gameState.incrementCalls();
        currentPlayerState.allBet += activePlayerBet - currentPlayerState.bet;
        if(_gameState.currentPlayerIsThePlayer())
        {
            _gameState.addYourBet(activePlayerBet - currentPlayerState.bet);
            emit yourBetChanged(_gameState.getYourBet());
        }
    }

    currentPlayerState.lastDesecition = activePlayerDecesion;
    currentPlayerState.bet = activePlayerBet;

    if(_gameState.searchNextAtivePlayer(_gameState.getCurrentPlayer()) == _gameState.getRoundStarter())
    {
        if(_gameState.getRound() == TexasHoldem::river)
        {
            emit endGame();
        }
        else
        {
            _gameState.changeBeforeBet();
        }
        if(_gameState.getRound() != TexasHoldem::river)
        {
            emit waitingCommunityCards();
            if( _gameState.getRound() == TexasHoldem::pre_flop)
            {
                emit selectCommunityCards(0,2);

            }
            else if(_gameState.getRound() == TexasHoldem::flop)
            {
                emit selectCommunityCards(3,3);
            }
            else if(_gameState.getRound() == TexasHoldem::turn)
            {
                emit selectCommunityCards(4,4);
            }

            _gameState.addTableToPot();
            _gameState.nextRound();
            emit potChanged(_gameState.getPot());
            emit choiceOptionsChanged(_gameState.isBeforeBet());
        }
        return;

    }
    else
    {
        _gameState.setCurrentPlayer(_gameState.searchNextAtivePlayer(_gameState.getCurrentPlayer()));
        emit activePlayerChanged(_gameState.getCurrentPlayer());
    }


    if(_gameState.currentPlayerIsThePlayer())
    {
        emit nextPlayerHint(_strategist.evaluate());
    }


}


void TexasHoldemModel::addCommunityCards(const std::list<Card> &cards)
{
    _validState = stateNotContainsCards(cards);

    if(_validState)
    {
        for(Card c : cards)
        {
            _gameState.addCommunityCard(c);
        }
    }
    else
    {
        emit invalidState("Community cards must be different!");
    }


}

std::pair<bool,QString> TexasHoldemModel::validateStepState(TexasHoldem::desecition activePlayerDecesion,int activePlayerBet)
{
    std::pair<bool,QString> errorState(false,"Error: ");
    if(activePlayerBet != _gameState.getMinimumBet()  && activePlayerDecesion == TexasHoldem::call)
    {
        errorState.first  = true;
        errorState.second.append("The bet must be the minimum bet amount!").append("\n");

    }

    if(activePlayerDecesion == TexasHoldem::raise &&
    activePlayerBet != (_gameState.getMinimumBet() + _gameState.getRaiseAmount()))
    {
        errorState.first = true;
        errorState.second.append("Wrong raised amount!\n");
    }

    if(activePlayerDecesion == TexasHoldem::bet && activePlayerBet != _gameState.getRaiseAmount())
    {
        errorState.first = true;
        errorState.second.append("The bet must be the raise amount!\n");
    }

    if(activePlayerDecesion == TexasHoldem::none)
    {
        errorState.first  = true;
        errorState.second.append("You must make a decesion!");
    }

    return errorState;

}

std::pair<bool, QString> TexasHoldemModel::validateStartingState(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_, std::pair<Card, Card> hand_)
{
    std::pair<bool,QString> errorState(false,"Error: ");
    if(playerNumber_ > players_)
    {
        errorState.first = true;
        errorState.second.append("Position of player must be less then number of players!\n");
    }
    if(smallBlindBet_*2 != bigBlindBet_)
    {
        errorState.first = true;
        errorState.second.append("The big blind's' bet must be two times more then small blind's!\n");
    }
    if(hand_.first == hand_.second)
    {
        errorState.first = true;
        errorState.second.append("The starting cards must be different!\n");
    }

    return errorState;




}

bool TexasHoldemModel::stateNotContainsCards(const std::list<Card> &cards)
{
    bool l = true;
    for (std::list<Card>::const_iterator it = cards.begin(); it != std::prev(cards.end()) && l; it++)
    {
        for (std::list<Card>::const_iterator it2 = std::next(it); it2 != cards.end() && l; it2++)
        {
            l = !(*it == *it2);
        }
    }

    if(l)
    {
        std::list<Card> notHiddenCards = _gameState.getAllUnHiddenCards();
        for(Card card : cards)
        {
           l = std::count_if(notHiddenCards.begin(),notHiddenCards.end(),[card](Card c) {return c == card;}) == 0;
           if(!l) break;
        }
    }

    return l;
}

}




