#include "gamingtableconfiguration.h"
#include <algorithm>

#include <assert.h>
namespace Model
{


GamingTableConfiguration::GamingTableConfiguration()
{
    init();
}

void GamingTableConfiguration::init()
{
    _hiddenCards.clear();
    for(int i = 2; i <= 14; i++ )
    {
        _hiddenCards.push_back(Card(i,TexasHoldem::color::clubs));
        _hiddenCards.push_back(Card(i,TexasHoldem::color::diamonds));
        _hiddenCards.push_back(Card(i,TexasHoldem::color::hearts));
        _hiddenCards.push_back(Card(i,TexasHoldem::color::spades));
    }

    std::for_each(_playersState.begin(),_playersState.end(),[](Player& player) { player.allBet = 0;});
    _beforeBet = false;
    _yourBet = 0;
    _nOfRaises = 0;
    _nOfCalls = 0;
    _pot = 0;
}

void GamingTableConfiguration::nextRound()
{
    switch(_round)
    {
    case TexasHoldem::pre_flop:
        _round = TexasHoldem::flop; break;
    case TexasHoldem::flop:
        _round = TexasHoldem::turn; break;
    case TexasHoldem::turn:
        _round = TexasHoldem::river; break;
    case TexasHoldem::river:
        _round = TexasHoldem::pre_flop;
        break;
    default:
        break;
    }
}

const std::list<Card>& GamingTableConfiguration::getHiddenCards() const
{
    return _hiddenCards;
}

void GamingTableConfiguration::setCommunityCards(const std::vector<Card> cards)
{
    _communityCards = cards;
    calculatedHiddenCards = false;
}

void GamingTableConfiguration::addCommunityCard(const Card &c)
{
    _communityCards.push_back(c);
    _hiddenCards.remove(c);
}

std::list<std::vector<Card> > GamingTableConfiguration::getPossibleNextRoundComminityCards()
{
    assert(_communityCards.size() > 0 && _communityCards.size() < 5);
    std::list<std::vector<Card> > possiblities;
    std::vector<Card> comm_cards;
    for(Card c : getHiddenCards())
    {
        comm_cards = _communityCards;
        comm_cards.push_back(c);
        possiblities.push_back(comm_cards);
    }

    return possiblities;
}

Pair GamingTableConfiguration::getYourHand() const
{
    return Pair(_yourCard1,_yourCard2);
}


void GamingTableConfiguration::setYourHand(const Card &c1, const Card &c2)
{
    _yourCard1 = c1;
    _yourCard2 = c2;
    _hiddenCards.remove(_yourCard1);
    _hiddenCards.remove(_yourCard2);
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

void GamingTableConfiguration::initPlayersBet()
{
    for(Player& player: _playersState)
    {
        player.bet = 0;
    }
}

void GamingTableConfiguration::serachFirstActivePlayer()
{
    int n = getNofStarterPlayer();
    int first = _round == TexasHoldem::pre_flop ? (2 % n) : 0;
    while(_playersState[first].lastDesecition == TexasHoldem::fold)
        first = (first + 1) % n;

    _roundStarterPlayer = first;
    _currentPlayer = first;

}

int GamingTableConfiguration::searchNextAtivePlayer(int current) const
{
    int n = getNofStarterPlayer();
    int next = (current + 1) % n;
    while(_playersState[next].lastDesecition == TexasHoldem::fold)
        next = (next + 1) % n;

    return next;
}

int GamingTableConfiguration::positionDiffRelatedToStarter(int pos) const
{
    int count = 0;
    int starter = pos;
    while(starter != getRoundStarter())
    {
        count++;
        starter = searchNextAtivePlayer(starter);
    }

    return count;
}

int GamingTableConfiguration::getPot() const
{
    return _pot;
}

void GamingTableConfiguration::setPot(int value)
{
    _pot = value;
}
}
