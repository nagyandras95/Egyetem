#include "game_configuration.h"

#include <assert.h>

game_configuration::game_configuration()
{
    for(int i = 2; i <= 14; i++ )
    {
        hidden_cards.push_back(card(i,card::color::clubs));
        hidden_cards.push_back(card(i,card::color::diamonds));
        hidden_cards.push_back(card(i,card::color::hearts));
        hidden_cards.push_back(card(i,card::color::spades));
    }
}

std::list<card> game_configuration::get_hidden_cards()
{
    hidden_cards.remove(your_card1);
    hidden_cards.remove(your_card2);
    for(card c : community_cards)
    {
        hidden_cards.remove(c);
    }

    return hidden_cards;
}

std::list<std::vector<card> > game_configuration::get_possible_next_round_community_cards()
{
    assert(community_cards.size() > 0 && community_cards.size() < 5);
    std::list<std::vector<card> > possiblities;
    std::vector<card> comm_cards;
    for(card c : get_hidden_cards())
    {
        comm_cards = community_cards;
        comm_cards.push_back(c);
        possiblities.push_back(comm_cards);
    }

    return possiblities;
}
