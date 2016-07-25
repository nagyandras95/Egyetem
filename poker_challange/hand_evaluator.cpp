#include <assert.h>

#include "hand_evaluator.h"
#include "game_configuration.h"

hand_evaluator::hand_evaluator() {}

double hand_evaluator::evaluate_hand(const std::list<card>& unknown_cards,const std::vector<card>& community_cards,const std::pair<card,card> your_cards)
{
    combination my_hand_comb = rank_hand(your_cards,community_cards);
    int ahead = 0, behind = 0;
    int count = 0;
    for(std::pair<card,card> p : get_all_pair(unknown_cards))
    {
        combination opp_comb = rank_hand(p,community_cards);
        if(my_hand_comb < opp_comb) ahead++;
        else behind++;

        count++;
    }

    return (double) ((double) behind)/((double) count);
}

combination hand_evaluator::rank_hand(const std::pair<card,card> p, const std::vector<card>& community_cards)
{

    std::vector<combination> combinations;
    std::vector<card> all_card(community_cards.begin(),community_cards.end());
    all_card.push_back(p.first);
    all_card.push_back(p.second);
    for(int i = 0; i < std::pow(2,all_card.size()); i++)
    {
        std::list<card> cards;
        std::vector<int> rep = get_reprezentation(i,all_card.size());
        int count_one = std::count_if(rep.begin(),rep.end(),[](int e) {return e == 1;});
        if(count_one <= 5 && count_one > 1)
        {

            for(int i = 0; i < (int)rep.size(); i++)
            {
                if(rep[i] == 1)
                {
                    cards.push_back(all_card[i]);
                }
            }


        }
        combinations.push_back(combination(cards));
    }
    assert(combinations.size() > 0);
    return *(std::max_element(combinations.begin(),combinations.end()));

}

std::vector<int> hand_evaluator::get_reprezentation(int i, int size)
{
    std::vector<int> rep(size);
    int c = 0;
    while(i != 0)
    {
        rep[c] = (i%2);
        i = (i - (i%2))/2;
        c++;
    }

    return rep;
}

std::list<std::pair<card, card> > hand_evaluator::get_all_pair(const std::list<card> &cards)
{
    std::list<std::pair<card,card> > all_pair;

    for(std::list<card>::const_iterator it1 = cards.begin(); it1 != std::prev(cards.end()); it1++)
    {

        for(std::list<card>::const_iterator it2 = std::next(it1); it2 != cards.end(); it2++)
        {
            all_pair.push_back(std::pair<card,card>(*it1,*it2));
        }

    }

    return all_pair;
}
