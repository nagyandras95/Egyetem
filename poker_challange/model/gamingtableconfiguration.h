#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include "card.h"
#include <vector>
#include <list>
#include "holdemtypes.h"


class GamingTableConfiguration
{
public:

    GamingTableConfiguration();
    void init();
    const std::list<card>& getHiddenCards();

    std::vector<card> getCommunityCards() const {return _communityCards;}
    void setCommunityCards(const std::vector<card> cards);
    void addCommunityCard(const card& c) {_communityCards.push_back(c);calculatedHiddenCards = false;}
    std::list<std::vector<card> > getPossibleNextRoundComminityCards();

    std::pair<card,card> getYourHand() const {return std::pair<card,card>(_yourCard1,_yourCard2);}
    void setYourHand(const card& c1,const card& c2);

    int getNOfActivePlayers() const;
    void setNOfActivePlayers(int value);
    void decrementNOfActivePlayers() {--_nOfActivePlayers;}

    int getPot() const;
    int getTotalPot() const {return _pot + _tableSumMoney;}
    void setPot(int value);
    void addPot(int value) {_pot += value;}

    int getYourBet() const;
    void setYourBet(int value);
    void addYourBet(int value) {_yourBet+= value;}


    int getRaises() {return _nOfRaises;}
    void initRaises() {_nOfRaises = 0;}
    void setNofRaises(int value) {_nOfRaises = value;}
    void incrementRaises() {_nOfRaises++;}

    void initTableSumMoney() {_tableSumMoney = 0;}
    void addTableMoney(int value) {_tableSumMoney += value;}

private:
    card _yourCard1;
    card _yourCard2;

    std::list<card> _hiddenCards;
    std::vector<card> _communityCards;

    int _nOfActivePlayers;
    int _pot;
    int _yourBet;
    int _tableSumMoney;
    int _nOfRaises;

    bool calculatedHiddenCards;




};
#endif // GAME_CONFIGURATION_H
