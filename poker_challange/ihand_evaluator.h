#ifndef IHAND_EVALUATOR_H
#define IHAND_EVALUATOR_H

#include <list>
#include <vector>

#include "game_configuration.h"
#include "card.h"



class ihand_evaluator
{
public:
    ihand_evaluator();
    virtual ~ihand_evaluator(){}
    virtual double evaluate_hand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>) = 0;


};

#endif // IHAND_EVALUATOR_H
