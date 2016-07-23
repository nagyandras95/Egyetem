#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include "card.h"
#include <list>

class game_configuration
{
public:
    enum options {check,call,raise,fold};
    enum round {pre_flop, flop, turn, river};

    game_configuration();
    std::list<card> get_hidden_cards();

    card your_card1;
    card your_card2;

    std::list<card> hidden_cards;
    std::list<card> community_cards;

    int number_of_all_players;
    int number_of_faied_players;

    int full_bet_amount;
    int your_bet;

    round current_round;

    bool small_bind;
    bool big_bind;

};
#endif // GAME_CONFIGURATION_H
