#include <assert.h>
#include <QDebug>

#include "handevaluator.h"
#include "gamingtableconfiguration.h"
#include "pair.h"

HandEvaluator::HandEvaluator() {}

double HandEvaluator::evaluateHand(const std::list<card>& unknown_cards,const std::vector<card>& community_cards,
                                   const std::pair<card,card> your_cards, const int players)
{
    combination my_hand_comb = rankHand(your_cards,community_cards);
    int ahead = 0;
    int n = (int) unknown_cards.size();
    int count = (n * (n - 1)) / 2;
    for(std::pair<card,card> p : getAllPair(unknown_cards))
    {
        combination opp_comb = rankHand(p,community_cards);
        if(my_hand_comb < opp_comb)
        {
            ahead++;
        }
    }

    long double c =  probabilityDistribution(count,ahead,players);
    return c;
}

double HandEvaluator::evaluatePair(const std::pair<card, card> p,const std::list<card>& unknown_cards, const int players)
{
    pair myPair = pair(p.first,p.second);
    int behind = 0;
    int n = (int) unknown_cards.size();
    int count = (n * (n - 1)) / 2;
    for(std::pair<card,card> p : getAllPair(unknown_cards))
    {
        pair oppPair = pair(p.first,p.second);
        if(oppPair <= myPair) behind++;
    }
    double c = behind/count;
    return c;

}

combination HandEvaluator::rankHand(const std::pair<card,card> p, const std::vector<card>& community_cards)
{

    std::vector<combination> combinations;
    std::vector<card> all_card(community_cards.begin(),community_cards.end());
    all_card.push_back(p.first);
    all_card.push_back(p.second);
    for(int i = 0; i < std::pow(2,all_card.size()); i++)
    {
        std::vector<card> cards;
        std::pair<std::vector<int>,int> p = getReprezentation(i,all_card.size());
        std::vector<int> rep = p.first;
        if(p.second == 5)
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

std::pair<std::vector<int>,int> HandEvaluator::getReprezentation(int i, int size)
{
    std::vector<int> rep(size);
    int c = 0;
    int count_one = 0;
    while(i != 0)
    {
        rep[c] = (i%2);
        if(rep[c] == 1)
            ++count_one;
        if(count_one > 5)
            break;

        i = (i - (i%2))/2;
        c++;

    }

    return std::pair<std::vector<int>, int>(rep,count_one);
}

std::list<std::pair<card, card> > HandEvaluator::getAllPair(const std::list<card> &cards)
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

long double HandEvaluator::probabilityDistribution(int N, int M, int n)
{
    int i = std::min(N-n,N-M), j = N;
    long double val = 1;
    while( (i >= N - M - (n - 1)) && (j >= std::max(N-M+1,N-n+1)) )
    {
        val *= (long double)i / (long double)j;
        i--;
        j--;
    }

    return val;
}
