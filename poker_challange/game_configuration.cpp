#include "game_configuration.h"

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
