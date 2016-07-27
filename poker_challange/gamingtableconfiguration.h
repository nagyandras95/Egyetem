#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include "card.h"
#include <vector>
#include <list>

class GamingTableConfiguration
{
public:
    enum options {check,call,raise,fold};
    enum round {pre_flop, flop, turn, river};

    GamingTableConfiguration();
    const std::list<card>& getHiddenCards();

    std::vector<card> getCommunityCards() const {return communityCards;}
    void setCommunityCards(const std::vector<card> cards) {communityCards = cards;}
    std::list<std::vector<card> > getPossibleNextRoundComminityCards();

    std::pair<card,card> getYourHand() const {return std::pair<card,card>(yourCard1,yourCard2);}
    void setYourHand(const card& c1,const card& c2) {yourCard1 = c1; yourCard2 = c2;}

    int getNOfActivePlayers() const;
    void setNOfActivePlayers(int value);

    int getPot() const;
    void setPot(int value);

    int getYourBet() const;
    void setYourBet(int value);

private:
    card yourCard1;
    card yourCard2;

    std::list<card> hiddenCards;
    std::vector<card> communityCards;

    int nOfActivePlayers;

    int pot;
    int yourBet;

    round current_round;


    bool calculatedHiddenCards;


};
#endif // GAME_CONFIGURATION_H
