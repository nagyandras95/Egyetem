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

    virtual double evaluate_hand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>,const int);
    virtual double evaluate_pair(const std::pair<card,card>, const std::list<card>&);
private:

    combination rank_hand(const std::pair<card,card>,const std::vector<card>&);
    int rank_pair(std::pair<card,card>);
    std::vector<int> get_reprezentation(int,int);
    std::list<std::pair<card,card> > get_all_pair(const std::list<card>&);

    long double probability_distribution(int,int,int);


};

#endif // HAND_EVALUATOR_H
