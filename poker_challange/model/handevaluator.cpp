#include <assert.h>
#include <QDebug>

#include "handevaluator.h"
#include "gamingtableconfiguration.h"
#include "pair.h"
#include "card.h"

namespace Model
{

HandEvaluator::HandEvaluator() {}

double HandEvaluator::evaluateHand(const std::list<Card>& unknownCards, const std::vector<Card>& communityCards,
                                   const Pair yourCards, const int players)
{
    Combination myHandComb = rankHand(std::pair<Card,Card>(yourCards.getFirstCard(),yourCards.getSecondCard()),communityCards);
    int ahead = 0;
    int n = (int) unknownCards.size();
    int count = (n * (n - 1)) / 2;
    for(std::pair<Card,Card> p : getAllPair(unknownCards))
    {
        Combination oppComb = rankHand(p,communityCards);
        if(myHandComb < oppComb)
        {
            ahead++;
        }
    }

    long double c =  probabilityDistribution(count,ahead,players);
    return c;
}

double HandEvaluator::evaluatePair(const Pair p, const std::list<Card>& unknownCards)
{
    Pair myPair = p;
    int behind = 0;
    int n = (int) unknownCards.size();
    int count = (n * (n - 1)) / 2;
    for(std::pair<Card,Card> p : getAllPair(unknownCards))
    {
        Pair oppPair = Pair(p.first,p.second);
        if(oppPair <= myPair) behind++;
    }
    double c = (double)behind/(double)count;
    return c;

}

Combination HandEvaluator::rankHand(const std::pair<Card,Card> p, const std::vector<Card>& community_cards)
{

    std::vector<Combination> combinations;
    std::vector<Card> allCard(community_cards.begin(),community_cards.end());
    allCard.push_back(p.first);
    allCard.push_back(p.second);
    for(int i = 0; i < std::pow(2,allCard.size()); i++)
    {
        std::vector<Card> cards;
        std::pair<std::vector<int>,int> p = getReprezentation(i,allCard.size());
        std::vector<int> rep = p.first;
        if(p.second == 5)
        {

            for(int i = 0; i < (int)rep.size(); i++)
            {
                if(rep[i] == 1)
                {
                    cards.push_back(allCard[i]);
                }
            }


        }
        combinations.push_back(Combination(cards));
    }
    assert(combinations.size() > 0);
    return *(std::max_element(combinations.begin(),combinations.end()));

}

/*
 * This function creates a reprezentaion of subset of 5 from hand combination by
 * marking the contained positionts by 1.
 */
std::pair<std::vector<int>,int> HandEvaluator::getReprezentation(int i, int size)
{
    std::vector<int> rep(size);
    int c = 0;
    int countOne = 0;
    while(i != 0 && countOne < 5)
    {
        rep[c] = (i%2);
        if(rep[c] == 1)
            ++countOne;

        i = (i - (i%2))/2;
        c++;

    }

    return std::pair<std::vector<int>, int>(rep,countOne);
}

std::list<std::pair<Card, Card> > HandEvaluator::getAllPair(const std::list<Card> &cards)
{
    std::list<std::pair<Card,Card> > allPair;

    for(std::list<Card>::const_iterator it1 = cards.begin(); it1 != std::prev(cards.end()); it1++)
    {

        for(std::list<Card>::const_iterator it2 = std::next(it1); it2 != cards.end(); it2++)
        {
            allPair.push_back(std::pair<Card,Card>(*it1,*it2));
        }

    }

    return allPair;
}


/*
 * A special case of probability distribution (k=0).
 * It's avoid calculating of factorial.
 */
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

}
