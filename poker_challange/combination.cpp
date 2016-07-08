#include "combination.h"
#include <algorithm>


int combination::PAIR_VALUE = 14*2;
int combination::DRILL_VAELUE = combination::PAIR_VALUE*3;
int combination::STRAIGHT_VALUE = combination::DRILL_VAELUE*2;
int combination::FLUSH_VALUE = combination::STRAIGHT_VALUE*2;
int combination::COLOR_SAME_VALUE = combination::STRAIGHT_VALUE*2;
int combination::POKER_VALUE = combination::COLOR_SAME_VALUE*2;
int combination::STARTIGHT_FLUSH_VALUE = combination::POKER_VALUE*2;


combination::combination(std::list<card> cards_) : cards(cards_)
{
    cards.sort();
    value = calc_value();
    max = *std::max_element(cards.begin(),cards.end());
}

int combination::calc_value()
{
    int number_of_pairs = 0;
    bool drill = false;
    bool poker = false;
    bool straight = true;
    bool all_same_color = true;
    bool same = true;
    int count_same_values = 1;
    std::list<card>::iterator it = cards.begin();
    int sum = it->get_number()*2;
    it++;
    for(;it != cards.end(); it++)
    {
        qDebug() << it->get_number();
        sum = sum + it->get_number();
        same = *std::prev(it) == *(it);
        all_same_color = all_same_color && std::prev(it)->get_color() == it->get_color();
        same ? count_same_values++ : count_same_values = 1;
        number_of_pairs = count_same_values == 2 ? number_of_pairs + 1 : number_of_pairs;
        drill = drill || count_same_values == 3;
        poker = poker || count_same_values == 4;
        straight = straight && ( (it->get_number() - std::prev(it)->get_number()) == 1);

    }

    return PAIR_VALUE*number_of_pairs + DRILL_VAELUE*drill + FLUSH_VALUE*(number_of_pairs > 0 && drill) + POKER_VALUE*poker +
            COLOR_SAME_VALUE*all_same_color + STRAIGHT_VALUE*straight + (all_same_color && straight)*STARTIGHT_FLUSH_VALUE + sum;

}



