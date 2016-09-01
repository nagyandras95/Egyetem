#include "gamingtableconfiguration.h"

#include <assert.h>

GamingTableConfiguration::GamingTableConfiguration()
{
    init();
}

void GamingTableConfiguration::init()
{
    _hiddenCards.clear();
    for(int i = 2; i <= 14; i++ )
    {
        _hiddenCards.push_back(card(i,card::color::clubs));
        _hiddenCards.push_back(card(i,card::color::diamonds));
        _hiddenCards.push_back(card(i,card::color::hearts));
        _hiddenCards.push_back(card(i,card::color::spades));
    }
    _yourBet = 0;
    _pot = 0;
    calculatedHiddenCards = false;
}

const std::list<card>& GamingTableConfiguration::getHiddenCards()
{
    if(!calculatedHiddenCards)
    {
        _hiddenCards.remove(_yourCard1);
        _hiddenCards.remove(_yourCard2);
        for(card c : _communityCards)
        {
            _hiddenCards.remove(c);
        }
        calculatedHiddenCards = true;
    }


    return _hiddenCards;
}

void GamingTableConfiguration::setCommunityCards(const std::vector<card> cards)
{
    _communityCards = cards;
    calculatedHiddenCards = false;
}

std::list<std::vector<card> > GamingTableConfiguration::getPossibleNextRoundComminityCards()
{
    assert(_communityCards.size() > 0 && _communityCards.size() < 5);
    std::list<std::vector<card> > possiblities;
    std::vector<card> comm_cards;
    for(card c : getHiddenCards())
    {
        comm_cards = _communityCards;
        comm_cards.push_back(c);
        possiblities.push_back(comm_cards);
    }

    return possiblities;
}

void GamingTableConfiguration::setYourHand(const card &c1, const card &c2)
{
    _yourCard1 = c1;
    _yourCard2 = c2;
    calculatedHiddenCards = false;
}


int GamingTableConfiguration::getNOfActivePlayers() const
{
    return _nOfActivePlayers;
}

void GamingTableConfiguration::setNOfActivePlayers(int value)
{
    _nOfActivePlayers = value;
}

int GamingTableConfiguration::getYourBet() const
{
    return _yourBet;
}

void GamingTableConfiguration::setYourBet(int value)
{
    _yourBet = value;
}

int GamingTableConfiguration::getPot() const
{
    return _pot;
}

void GamingTableConfiguration::setPot(int value)
{
    _pot = value;
}
