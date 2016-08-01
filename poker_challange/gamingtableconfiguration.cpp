#include "gamingtableconfiguration.h"

#include <assert.h>

GamingTableConfiguration::GamingTableConfiguration()
{
    init();
}

void GamingTableConfiguration::init()
{
    hiddenCards.clear();
    for(int i = 2; i <= 14; i++ )
    {
        hiddenCards.push_back(card(i,card::color::clubs));
        hiddenCards.push_back(card(i,card::color::diamonds));
        hiddenCards.push_back(card(i,card::color::hearts));
        hiddenCards.push_back(card(i,card::color::spades));
    }

    calculatedHiddenCards = false;
}

const std::list<card>& GamingTableConfiguration::getHiddenCards()
{
    if(!calculatedHiddenCards)
    {
        hiddenCards.remove(yourCard1);
        hiddenCards.remove(yourCard2);
        for(card c : communityCards)
        {
            hiddenCards.remove(c);
        }
        calculatedHiddenCards = true;
    }


    return hiddenCards;
}

void GamingTableConfiguration::setCommunityCards(const std::vector<card> cards)
{
    communityCards = cards;
    calculatedHiddenCards = false;
}

std::list<std::vector<card> > GamingTableConfiguration::getPossibleNextRoundComminityCards()
{
    assert(communityCards.size() > 0 && communityCards.size() < 5);
    std::list<std::vector<card> > possiblities;
    std::vector<card> comm_cards;
    for(card c : getHiddenCards())
    {
        comm_cards = communityCards;
        comm_cards.push_back(c);
        possiblities.push_back(comm_cards);
    }

    return possiblities;
}

void GamingTableConfiguration::setYourHand(const card &c1, const card &c2)
{
    yourCard1 = c1;
    yourCard2 = c2;
    calculatedHiddenCards = false;
}


int GamingTableConfiguration::getNOfActivePlayers() const
{
    return nOfActivePlayers;
}

void GamingTableConfiguration::setNOfActivePlayers(int value)
{
    nOfActivePlayers = value;
}

int GamingTableConfiguration::getYourBet() const
{
    return yourBet;
}

void GamingTableConfiguration::setYourBet(int value)
{
    yourBet = value;
}

int GamingTableConfiguration::getPot() const
{
    return pot;
}

void GamingTableConfiguration::setPot(int value)
{
    pot = value;
}
