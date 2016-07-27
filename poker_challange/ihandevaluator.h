#ifndef IHAND_EVALUATOR_H
#define IHAND_EVALUATOR_H

#include <list>
#include <vector>

#include "gamingtableconfiguration.h"
#include "card.h"



class IHandEvaluator
{
public:
    IHandEvaluator();
    virtual ~IHandEvaluator(){}
    virtual double evaluate_hand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>, const int) = 0;
    virtual double evaluate_pair(const std::pair<card,card>, const std::list<card>&) = 0;


};

#endif // IHAND_EVALUATOR_H
