#include "combination.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include "holdemtypes.h"
#include <QDebug>


combination::combination(std::vector<card> cards_) : _cards(cards_)
{
    std::sort(_cards.begin(),_cards.end());
    _value = calcValue();
}

int combination::calcValue()
{
    int comb_size = (int) _cards.size();
    int number_of_pairs = 0;
    bool drill = false;
    bool poker = false;
    bool straight = comb_size == 5;
    bool all_same_color = comb_size == 5;
    bool same;
    int count_same_values = 1;
    for(int i = 1;i < comb_size; ++i)
    {
        same = _cards[i-1].get_number() == _cards[i].get_number();
        int prev_count = count_same_values;
        all_same_color = all_same_color && _cards[i-1].get_color() == _cards[i].get_color();
        same ? count_same_values++ : count_same_values = 1;

        if(prev_count == 2 && count_same_values == 1)
            critical_cards.push_back(_cards[i-1].get_number());
        else if(count_same_values == 3)
            critical_cards.push_back(_cards[i-1].get_number() + TexasHoldem::MAX_VALUE);
        else if(count_same_values == 1 && prev_count == 1)
        {
            secondary_cards.push_back(_cards[i-1].get_number());
            ctiric_second_uinon.push_back(_cards[i-1].get_number());
        }

        if(i == (comb_size - 1))
        {
            if(count_same_values == 1)
            {
                secondary_cards.push_back(_cards[i].get_number());
                ctiric_second_uinon.push_back(_cards[i].get_number());
            }

            else if(count_same_values == 2)
                 critical_cards.push_back(_cards[i].get_number());

        }

        number_of_pairs = count_same_values == 2 ? number_of_pairs + 1 : number_of_pairs;
        drill = drill || count_same_values == 3;
        poker = poker || count_same_values == 4;
        straight = straight && ( (_cards[i].get_number() - _cards[i-1].get_number()) == 1);

    }

    if(all_same_color || straight)
    {
        ctiric_second_uinon.clear();
        for(card c : _cards)
        {
            ctiric_second_uinon.push_back(c.get_number());
        }


    }
    else
    {
        for(int val : critical_cards)
            ctiric_second_uinon.push_back(val);
    }




    if(number_of_pairs != 0 && !drill && !poker && !all_same_color)
    {
        if(number_of_pairs == 1)
            return TexasHoldem::PAIR_VALUE;
        else
            return TexasHoldem::TWO_PAIR_VALUE;
    }
    else if(drill && !poker && !all_same_color && number_of_pairs == 1)
        return TexasHoldem::DRILL_VALUE;
    else if(all_same_color && !straight)
        return TexasHoldem::FLUSH_VALUE;
    else if(poker)
        return TexasHoldem::POKER_VALUE;
    else if(number_of_pairs == 2 && drill)
        return TexasHoldem::FULL_HOUSE_VALUE;
    else if(straight && !all_same_color)
        return TexasHoldem::STRAIGHT_VALUE;
    else if(all_same_color && straight)
        return TexasHoldem::STARTIGHT_FLUSH_VALUE;
    else
        return 0;

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
    int val1 = c1.getValue();
    int val2 = c2.getValue();
    if(val1 != val2)
    {
        return val1 < val2;
    }
    else
    {
        if(c1.getNofCards() != c2.getNofCards()) return c1.getNofCards() < c2.getNofCards();
        return is_better(c1.getDecisiveCards(),c2.getDecisiveCards());


    }
}
