#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H

#include <list>
#include <set>
#include <vector>
#include "card.h"
#include <math.h>
#include "combination.h"

struct configuration
{
    enum options {check,call,raise,fold};
    enum round {pre_flop, flop, turn, river};


    configuration()
    {
        for(int i = 2; i <= 14; i++ )
        {
            hidden_cards.push_back(card(i,color::clubs));
            hidden_cards.push_back(card(i,color::diamonds));
            hidden_cards.push_back(card(i,color::hearts));
            hidden_cards.push_back(card(i,color::spades));
        }
    }

    std::list<card> get_hidden_cards()
    {
         hidden_cards.remove(your_card1);
         hidden_cards.remove(your_card2);
         for(card c : community_cards)
         {
             hidden_cards.remove(c);
         }

         return hidden_cards;
    }

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

class hand_evaluator
{
public:
    hand_evaluator();

    configuration game_state;

    configuration::options next_hint();
    int evaluate_hand();
    int rank_hand(std::pair<card,card> p);
    std::vector<int> get_reprezentation(int i, int size);
    std::list<std::pair<card,card> > get_all_pair(const std::list<card>& cards);


};

#endif // HAND_EVALUATOR_H
