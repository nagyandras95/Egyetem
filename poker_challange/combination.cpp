#include "combination.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include <QDebug>

int combination::MAX_VALUE = 14;
int combination::PAIR_VALUE = combination::MAX_VALUE*2;
int combination::DRILL_VALUE = combination::PAIR_VALUE*4;
int combination::STRAIGHT_VALUE = combination::DRILL_VALUE*2;
int combination::FLUSH_VALUE = combination::STRAIGHT_VALUE*2;
int combination::FULL_HOUSE_VALUE = combination::FLUSH_VALUE*2;
int combination::POKER_VALUE = combination::FULL_HOUSE_VALUE*2;
int combination::STARTIGHT_FLUSH_VALUE = combination::POKER_VALUE*2;


combination::combination(std::list<card> cards_) : cards(cards_)
{
    cards.sort();
    value = calc_value();
}

int combination::calc_value()
{
    int comb_size = (int) cards.size();
    int number_of_pairs = 0;
    bool drill = false;
    bool poker = false;
    bool straight = comb_size == 5;
    bool all_same_color = comb_size == 5;
    bool same;
    int count_same_values = 1;
    std::list<card>::iterator it = cards.begin();
    it++;
    for(;it != cards.end(); it++)
    {
        same = std::prev(it)->get_number() == (it)->get_number();
        int prev_count = count_same_values;


        all_same_color = all_same_color && std::prev(it)->get_color() == it->get_color();

        same ? count_same_values++ : count_same_values = 1;

        assert(count_same_values >= 1 &&  count_same_values <= 4);

        if(prev_count == 2 && count_same_values == 1)
            critical_cards.push_back(std::prev(it)->get_number());
        else if(count_same_values == 3)
            critical_cards.push_back(std::prev(it)->get_number() + combination::MAX_VALUE);
        else if(count_same_values == 1 && prev_count == 1)
        {
            secondary_cards.push_back(std::prev(it)->get_number());
            ctiric_second_uinon.push_back(std::prev(it)->get_number());
        }

        if(std::next(it) == cards.end())
        {
            if(count_same_values == 1)
            {
                secondary_cards.push_back(it->get_number());
                ctiric_second_uinon.push_back(it->get_number());
            }

            else if(count_same_values == 2)
              critical_cards.push_back(it->get_number());

        }




        number_of_pairs = count_same_values == 2 ? number_of_pairs + 1 : number_of_pairs;
        drill = drill || count_same_values == 3;
        poker = poker || count_same_values == 4;
        straight = straight && ( (it->get_number() - std::prev(it)->get_number()) == 1);

    }

    if(all_same_color || straight)
    {
        critical_cards.clear();
        secondary_cards.clear();
        ctiric_second_uinon.clear();
        for(card c : cards)
        {
            secondary_cards.push_back(c.get_number());
            ctiric_second_uinon.push_back(c.get_number());
        }


    }

    for(int val : critical_cards)
        ctiric_second_uinon.push_back(val);



    return PAIR_VALUE*(number_of_pairs*!((int)drill)*!((int)poker)*!((int)all_same_color)) +
            DRILL_VALUE*drill*(!(int)poker)*((int) number_of_pairs == 1)*!((int)all_same_color) +
            FLUSH_VALUE*( (all_same_color && !straight ) ) +
            POKER_VALUE* ((int)poker) +
            FULL_HOUSE_VALUE * ( (int) number_of_pairs == 2 && drill ) +
            STRAIGHT_VALUE * ((int) (straight) * (int) !all_same_color ) +
            STARTIGHT_FLUSH_VALUE*(all_same_color && straight);

}

bool is_better(const std::vector<int>& cards1, const std::vector<int>& cards2)
{

    assert(cards1.size() == cards2.size());
    bool l = false;
    bool gr = false;
    for(int i = (int)cards1.size() - 1; i >= 0  && !l; i--)
    {
            l = cards2[i] != cards1[i];
            gr = cards2[i] > cards1[i];
    }

    return gr;
}

bool operator<(const combination c1, const combination c2)
{
    int val1 = c1.get_value();
    int val2 = c2.get_value();
    if(val1 != val2)
    {
        return val1 < val2;
    }
    else
    {
        if(c1.get_nof_cards() != c2.get_nof_cards()) return c1.get_nof_cards() < c2.get_nof_cards();
        return is_better(c1.get_decisive_cards(),c2.get_decisive_cards());


    }
}
