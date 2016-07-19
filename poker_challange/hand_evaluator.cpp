#include "hand_evaluator.h"

hand_evaluator::hand_evaluator()
{

}

configuration::options hand_evaluator::next_hint()
{


    return configuration::options::fold;
}

int hand_evaluator::evaluate_hand()
{
    const std::list<card> unknown_cards = game_state.get_hidden_cards();
    int my_hand_value = rank_hand(std::pair<card,card>(game_state.your_card1,game_state.your_card2));
    int ahead = 0, behind = 0;
    for(std::pair<card,card> p : get_all_pair(unknown_cards))
    {
        int opp_value = rank_hand(p);
        if(my_hand_value < opp_value ) ahead++;
        else behind++;
    }

    return behind/ahead;
}

int hand_evaluator::rank_hand(std::pair<card, card> p)
{
    std::vector<card> c_cards;
    for(card c : game_state.community_cards)
    {
        c_cards.push_back(c);
    }

    std::vector<combination> combinations;
    for(int i = 0; i < std::pow(2,c_cards.size()); i++)
    {
        std::vector<int> rep = get_reprezentation(i,c_cards.size());
        if(std::count_if(rep.begin(),rep.end(),[](int e) {return e == 1;}) <= 3 )
        {
            std::list<card> cards;
            cards.push_back(p.first);
            cards.push_back(p.second);
            for(int i = 0; i < (int)rep.size(); i++)
            {
                if(rep[i] == 1)
                {
                    cards.push_back(c_cards[i]);
                }
            }

            combinations.push_back(combination(cards));
        }
    }

    return std::max_element(combinations.begin(),combinations.end())->get_value();

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
