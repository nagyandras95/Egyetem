#ifndef IHAND_EVALUATOR_H
#define IHAND_EVALUATOR_H

#include <list>
#include <vector>

#include "card.h"



class IHandEvaluator
{
public:
    IHandEvaluator() {}
    virtual ~IHandEvaluator(){}
    virtual double evaluateHand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>, const int) = 0;
    virtual double evaluatePair(const std::pair<card,card>, const std::list<card>&,const int) = 0;


};

#endif // IHAND_EVALUATOR_H
