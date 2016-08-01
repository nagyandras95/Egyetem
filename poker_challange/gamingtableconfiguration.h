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

    std::vector<card> getCommunityCards() const {return communityCards;}
    void setCommunityCards(const std::vector<card> cards);
    void addCommunityCard(const card& c) {communityCards.push_back(c);}
    std::list<std::vector<card> > getPossibleNextRoundComminityCards();

    std::pair<card,card> getYourHand() const {return std::pair<card,card>(yourCard1,yourCard2);}
    void setYourHand(const card& c1,const card& c2);

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

    bool calculatedHiddenCards;


};
#endif // GAME_CONFIGURATION_H
