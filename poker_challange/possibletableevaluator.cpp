#include "possibletableevaluator.h"
#include "handevaluator.h"
#include <list>
#include <vector>
#include <assert.h>

PossibleTableEvaluator::PossibleTableEvaluator()
{
    _chance = 0;
    _evaluator = new HandEvaluator();
}

void PossibleTableEvaluator::evalauteChance()
{
    _terminated = false;
    _chance = 0;
    startQueues();

    std::thread loader(&PossibleTableEvaluator::superimposeCards,this);
    for(int i = 0; i < _nOfThrads; ++i)
    {
        _workers.push_back(new std::thread(&PossibleTableEvaluator::task,this));
    }

    unsigned int size = _unknownCards.size();
    double val;
    for(unsigned int i = 0; i < size; ++i)
    {
        _evalautedValueQueue.dequeue(val);
        _chance += (val / size);
    }

    _terminated = true;
    _cardQueue.stopQueue();
    _evalautedValueQueue.stopQueue();

    assert((int)_workers.size() == _nOfThrads);
    for(int i = 0; i < _nOfThrads; ++i)
    {
        _workers[i]->join();
        delete _workers[i];

    }

    _workers.clear();
    loader.join();
}

void PossibleTableEvaluator::task()
{
    std::list<card> ownUnknownCards = _unknownCards;
    std::vector<card> ownCommunityCards = _communityCards;
    int size = (int) ownCommunityCards.size();
    ownCommunityCards.resize(size+1);
    while(!_terminated)
    {
        card c;
        _cardQueue.dequeue(c);
        ownCommunityCards[size] = c;
        ownUnknownCards.remove(c);

        _evalautedValueQueue.enque(_evaluator->evaluate_hand(ownUnknownCards,ownCommunityCards,_pair,_players));


         ownUnknownCards.push_back(c);
    }
}

void PossibleTableEvaluator::superimposeCards()
{
    for(card c : _unknownCards)
    {
        _cardQueue.enque(c);
    }

}

void PossibleTableEvaluator::startQueues()
{
    _cardQueue.startQueue();
    _evalautedValueQueue.startQueue();
}
