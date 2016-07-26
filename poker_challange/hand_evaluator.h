#ifndef HAND_EVALUATOR_H
#define HAND_EVALUATOR_H

#include <list>
#include <set>
#include <vector>
#include "card.h"
#include <math.h>
#include "ihand_evaluator.h"
#include "combination.h"
#include "game_configuration.h"

class hand_evaluator : public ihand_evaluator
{
public:
    hand_evaluator();
    virtual ~hand_evaluator(){}

    virtual double evaluate_hand(const std::list<card>&,const std::vector<card>&,const std::pair<card,card>);
    virtual double evaluate_pair(const std::pair<card,card>);
private:

    combination rank_hand(const std::pair<card,card>,const std::vector<card>&);
    std::vector<int> get_reprezentation(int,int);
    std::list<std::pair<card,card> > get_all_pair(const std::list<card>&);


};

#endif // HAND_EVALUATOR_H
