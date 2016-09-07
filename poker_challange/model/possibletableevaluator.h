#ifndef POSSIBLETABLEEVALUATOR_H
#define POSSIBLETABLEEVALUATOR_H


#include "ihandevaluator.h"
#include "threadsafequeue.h"
#include "card.h"
#include "gamingtableconfiguration.h"
#include <list>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>


/*
 * This class is suitable to create the possibles table states
 * and evaulate the possible rank of our hand in distirbuted way.
 */

namespace Model
{
class PossibleTableEvaluator
{
public:
    PossibleTableEvaluator(const GamingTableConfiguration& state_);

    void evalauteChance();
    double getChance() {return _chance;}

    void setNofWorkerThread(int n) {_nOfThrads = n;}

private:

    void task();
    void superimposeCards();

    void startQueues();
    void stopQueues();

    const GamingTableConfiguration& _gameState;

    IHandEvaluator* _evaluator;
    double _chance;

    Thread::ThreadSafeQueue<Card> _cardQueue;
    Thread::ThreadSafeQueue<double> _evalautedValueQueue;

    std::atomic_bool _terminated;
    int _nOfThrads = 1;
    std::vector<std::thread*> _workers;
    std::condition_variable _cond;


};
}



#endif // POSSIBLETABLEEVALUATOR_H
