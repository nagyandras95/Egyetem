#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include <vector>
#include <list>
#include "holdemtypes.h"
#include "card.h"
#include "player.h"
#include "pair.h"

namespace Model
{

class GamingTableConfiguration
{
public:

    GamingTableConfiguration();
    void init();
    void nextRound();
    void firstRound() {_round = TexasHoldem::pre_flop;}
    TexasHoldem::round getRound() const {return _round;}
    const std::list<Card>& getHiddenCards() const;

    std::list<Card> getAllUnHiddenCards() const
    {
        std::list<Card> cards;
        cards.push_back(_yourCard1);
        cards.push_back(_yourCard2);
        for(Card card : _communityCards)
        {
            cards.push_back(card);
        }
        return cards;
    }

    std::vector<Card> getCommunityCards() const {return _communityCards;}
    void setCommunityCards(const std::vector<Card> cards);
    void addCommunityCard(const Card& c);
    std::list<std::vector<Card> > getPossibleNextRoundComminityCards();

    Pair getYourHand() const;
    void setYourHand(const Card& c1,const Card& c2);

    int getNOfActivePlayers() const;
    void setNOfActivePlayers(int value);
    void decrementNOfActivePlayers() {--_nOfActivePlayers;}

    void initNofStartedPlayer(int n) {_nOfStarerPlayer = n;}
    int getNofStarterPlayer() const {return _nOfStarerPlayer;}

    int getPot() const;
    int getTotalPot() const {return _pot + _tableSumMoney;}
    void setPot(int value);
    void addPot(int value) {_pot += value;}
    void addTableToPot() {_pot += _tableSumMoney;}

    int getYourBet() const;
    void setYourBet(int value);
    void addYourBet(int value) {_yourBet+= value;}


    int getRaises() const {return _nOfRaises;}
    void initRaises() {_nOfRaises = 0;}
    void setNofRaises(int value) {_nOfRaises = value;}
    void incrementRaises() {_nOfRaises++;}

    int getCalls() const {return _nOfCalls;}
    void initCalls() {_nOfCalls = 0;}
    void setNofCalls(int value) {_nOfCalls = value;}
    void incrementCalls() {_nOfCalls++;}

    void initTableSumMoney() {_tableSumMoney = 0;}
    void addTableMoney(int value) {_tableSumMoney += value;}

    void setMinimumBet(int value) {_minimumBet = value;}
    int getMinimumBet() const {return _minimumBet;}

    void setBigBlind(int value) {_bigBlingBet = value;}
    int getRaiseAmount() const {return (_round == TexasHoldem::pre_flop || _round == TexasHoldem::flop) ? _bigBlingBet : 2*_bigBlingBet; }

    void setRoundStarter(int pos) {_roundStarterPlayer = pos;}
    int getRoundStarter() const {return _roundStarterPlayer;}

    void setPlayerPosition(int pos) {_playerPosition = pos;}
    int getPlayerPosition() const {return _playerPosition;}

    void changeBeforeBet() {_beforeBet = !_beforeBet;}
    bool isBeforeBet() const {return _beforeBet;}

    void setCurrentPlayer(int pos) {_currentPlayer = pos;}
    int getCurrentPlayer() const {return _currentPlayer;}
    bool currentPlayerIsThePlayer() const {return _playerPosition == _currentPlayer;}
    bool roundStarterIsThePlayer() const {return _roundStarterPlayer == _playerPosition;}
    bool playerIsSmallBlind() const {return _playerPosition == 0;}
    bool playerIsBigBlind() const {return _playerPosition == 1;}
    bool isRoundStarter(int pos) const {return pos == _roundStarterPlayer;}

    void initPlayersBet();

    const std::vector<Player> getPlayersState() const {return _playersState;}
    void resizePlayerState(int n) {_playersState.resize(n);}
    Player& getPositionedPlayer(int pos) {return _playersState[pos];}
    const Player& getPositionedPlayer(int pos) const {return _playersState[pos];}
    Player& getCurrentPlayerState() { return _playersState[_currentPlayer];}
    const Player& getCurrentPlayerState() const { return _playersState[_currentPlayer];}
    const Player& getThePlayerState() const {return _playersState[_playerPosition];}

    void serachFirstActivePlayer();
    int searchNextAtivePlayer(int current) const;
    int positionDiffRelatedToStarter(int pos) const;


private:

    Card _yourCard1;
    Card _yourCard2;

    std::list<Card> _hiddenCards;
    std::vector<Card> _communityCards;

    int _nOfActivePlayers;
    int _nOfStarerPlayer;
    int _pot;
    int _yourBet;
    int _tableSumMoney;
    int _nOfRaises;
    int _nOfCalls;
    int _minimumBet;
    int _bigBlingBet;
    int _roundStarterPlayer;
    int _playerPosition;
    int _currentPlayer;
    bool _beforeBet;

    TexasHoldem::round _round;
    std::vector<Player> _playersState;

    bool calculatedHiddenCards;

};


}
#endif // GAME_CONFIGURATION_H
