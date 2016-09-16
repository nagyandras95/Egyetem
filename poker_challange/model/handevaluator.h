#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H

#include <list>
#include <vector>
#include <math.h>
#include "ihandevaluator.h"
#include "card.h"
#include "combination.h"
#include "gamingtableconfiguration.h"
#include "pair.h"

namespace Model
{

class HandEvaluator : public IHandEvaluator
{
public:
    HandEvaluator();
    virtual ~HandEvaluator(){}

    virtual double evaluateHand(const std::list<Card>&unknownCards, const std::vector<Card>&communityCards, const Pair yourCards, const int);
    virtual double evaluatePair(const Pair, const std::list<Card>&, const int);

private:

    Combination rankHand(const std::pair<Card,Card>,const std::vector<Card>&);

    std::pair<std::vector<int>,int> getReprezentation(int,int);
    std::list<std::pair<Card,Card> > getAllPair(const std::list<Card>&);
    long double probabilityDistribution(int,int,int);

    std::list<Card> unknwonCards;
    std::list<std::pair<Card,Card> > allPair;


};
}
#endif // HAND_EVALUATOR_H
