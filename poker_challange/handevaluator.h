#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H

#include <list>
#include <set>
#include <vector>
#include <math.h>
#include "ihandevaluator.h"
#include "card.h"
#include "combination.h"
#include "gamingtableconfiguration.h"

class HandEvaluator : public IHandEvaluator
{
public:
    HandEvaluator();
    virtual ~HandEvaluator(){}

    virtual double evaluateHand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>,const int);
    virtual double evaluatePair(const std::pair<card,card>, const std::list<card>&, const int);

private:

    combination rankHand(const std::pair<card,card>,const std::vector<card>&);
    int rankPair(std::pair<card,card>);

    std::pair<std::vector<int>,int> getReprezentation(int,int);

    std::list<std::pair<card,card> > getAllPair(const std::list<card>&);

    long double probabilityDistribution(int,int,int);

    std::list<card> unknwonCards;
    std::list<std::pair<card,card> > allPair;


};

#endif // HAND_EVALUATOR_H
