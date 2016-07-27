#ifndef GAME_CONFIGURATION_H
#define GAME_CONFIGURATION_H

#include "card.h"
#include <vector>
#include <list>

class GamingTableConfigurationn
{
public:
    enum options {check,call,raise,fold};
    enum round {pre_flop, flop, turn, river};

    GamingTableConfiguration();
    std::list<card> get_hidden_cards();

    std::vector<card> get_community_cards() {return community_cards; }
    std::list<std::vector<card> > get_possible_next_round_community_cards();

    std::pair<card,card> get_your_pair() {return std::pair<card,card>(your_card1,your_card2);}

    card your_card1;
    card your_card2;

    std::list<card> hidden_cards;
    std::vector<card> community_cards;

    int number_of_all_players;
    int number_of_faied_players;

    int full_bet_amount;
    int your_bet;

    round current_round;

};
#endif // GAME_CONFIGURATION_H
