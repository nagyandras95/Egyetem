#include <assert.h>

#include "hand_evaluator.h"
#include "gamingtableconfiguration.h"

HandEvaluator::HandEvaluator() {}

double HandEvaluator::evaluate_hand(const std::list<card>& unknown_cards,const std::vector<card>& community_cards,const std::pair<card,card> your_cards, const int players)
{
    combination my_hand_comb = rank_hand(your_cards,community_cards);
    int ahead = 0;
    int n = (int) unknown_cards.size();
    int count = (n * (n - 1)) / 2 ;
    for(std::pair<card,card> p : get_all_pair(unknown_cards))
    {
        combination opp_comb = rank_hand(p,community_cards);
        if(my_hand_comb < opp_comb) ahead++;
    }

    long double c =  probability_distribution(count,ahead,players);
    return c;
}

double HandEvaluator::evaluate_pair(const std::pair<card, card> p,const std::list<card>& unknown_cards)
{
    int my_pair_rank = rank_pair(p);
    int ahead = 0, behind = 0;
    int count = 0;
    for(std::pair<card,card> p : get_all_pair(unknown_cards))
    {
        int opp_rank = rank_pair(p);
        if(my_pair_rank < opp_rank) ahead++;
        else if(my_pair_rank > opp_rank) behind++;

        count++;
    }
    return (double) ((double) behind)/((double) count);

}

combination HandEvaluator::rank_hand(const std::pair<card,card> p, const std::vector<card>& community_cards)
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

int HandEvaluator::rank_pair(std::pair<card, card> p)
{
    bool n_same = false, c_same = false, poss_staright = false;
    n_same = p.first.get_number() == p.second.get_number();
    c_same = p.first.get_color() == p.second.get_color();
    poss_staright = std::abs(p.first.get_number() - p.second.get_number()) <= 4 && !n_same;

    int def = 4*14;
    return n_same*def + c_same*def*2 +  poss_staright*def*4 + std::max(p.first,p.second).get_number();
}

std::vector<int> HandEvaluator::get_reprezentation(int i, int size)
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

std::list<std::pair<card, card> > HandEvaluator::get_all_pair(const std::list<card> &cards)
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

long double HandEvaluator::probability_distribution(int N, int M, int n)
{
   unsigned long long ratio = 1;
   unsigned long long div = 1;
   for(int i = std::min(N-n,N-M); i >= N - M - (n - 1); i--)
   {
       ratio *= i;
   }

   for(int i = N; i >= std::max(N-M+1,N-n+1); i--)
   {
       div *= i;
   }
    long double val = (long double)ratio / (long double)div;

   return val;
}

int HandEvaluator::variation(int n, int k)
{
    assert(n >= k);
    return fact(n) / (fact(k)*fact(n-k));
}

long HandEvaluator::fact(int n)
{
    assert(n >= 0);

    long f = 1;
    for(int i = 1; i <= n; i++)
    {
        f = f * (long)i;
    }


    return f;
}
