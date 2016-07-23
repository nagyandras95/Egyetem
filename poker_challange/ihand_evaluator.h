#ifndef IHAND_EVALUATOR_H
#define IHAND_EVALUATOR_H
#include "game_configuration.h"

class Ihand_evaluator
{
public:
    Ihand_evaluator();
    virtual ~Ihand_evaluator(){}
    virtual game_configuration::options next_hint() = 0;
    virtual double evaluate_hand() = 0;
    virtual void set_state(game_configuration) = 0;


};

#endif // IHAND_EVALUATOR_H
