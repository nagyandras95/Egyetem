#ifndef IHAND_EVALUATOR_H
#define IHAND_EVALUATOR_H

#include <list>
#include <vector>

#include "pair.h"
#include "card.h"

namespace Model
{

/*
 * Interface for hand evaluator
 */
class IHandEvaluator
{
public:
    IHandEvaluator() {}
    virtual ~IHandEvaluator(){}
    /*
     * This function is suitable to evaluate a streingth of poker hand according to other possible paires.
     */
    virtual double evaluateHand(const std::list<Card>&,const std::vector<Card>&,const Pair, const int) = 0;
    /*
     *  This function is suitable to evaluate a streingth of starting pair according to other possible paires.
     */
    virtual double evaluatePair(const Pair, const std::list<Card>&, const int) = 0;

};
}



#endif // IHAND_EVALUATOR_H
