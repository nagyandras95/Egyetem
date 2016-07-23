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

class hand_evaluator : public Ihand_evaluator
{
public:
    hand_evaluator();
    virtual ~hand_evaluator(){}


    virtual game_configuration::options next_hint();
    virtual double evaluate_hand();
    virtual void set_state(game_configuration state_) {this->game_state = state_;}

    game_configuration game_state;
private:
    combination rank_hand(std::pair<card,card>);
    std::vector<int> get_reprezentation(int,int);
    std::list<std::pair<card,card> > get_all_pair(const std::list<card>&);


};

#endif // HAND_EVALUATOR_H
