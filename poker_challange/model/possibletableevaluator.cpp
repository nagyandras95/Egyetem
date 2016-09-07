#include "possibletableevaluator.h"
#include "handevaluator.h"
#include <list>
#include <vector>
#include <assert.h>

namespace Model
{
PossibleTableEvaluator::PossibleTableEvaluator(const GamingTableConfiguration &state_) : _gameState(state_)
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

    unsigned int size = _gameState.getHiddenCards().size();
    double val;
    for(unsigned int i = 0; i < size; ++i)
    {
        _evalautedValueQueue.dequeue(val);
        /*
         * The val contains how many my chance is to win the game with this possible table state
         * and the total probability thesis can be used to calculate my real chance with the actucal state.
         */
        _chance += (val / size);
    }

    _terminated = true;
    stopQueues();

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
    std::list<Card> ownUnknownCards = _gameState.getHiddenCards();
    std::vector<Card> ownCommunityCards = _gameState.getCommunityCards();
    int size = (int) ownCommunityCards.size();
    ownCommunityCards.resize(size+1);
    while(!_terminated)
    {
        Card c;
        _cardQueue.dequeue(c);
        ownCommunityCards[size] = c;
        ownUnknownCards.remove(c);

        _evalautedValueQueue.enque(_evaluator->evaluateHand(ownUnknownCards,ownCommunityCards,
                                                            _gameState.getYourHand(),_gameState.getNOfActivePlayers()));
         ownUnknownCards.push_back(c);
    }
}

void PossibleTableEvaluator::superimposeCards()
{
    for(Card c : _gameState.getHiddenCards())
    {
        _cardQueue.enque(c);
    }

}

void PossibleTableEvaluator::startQueues()
{
    _cardQueue.startQueue();
    _evalautedValueQueue.startQueue();
}

void PossibleTableEvaluator::stopQueues()
{
    _cardQueue.stopQueue();
    _evalautedValueQueue.stopQueue();
}
}


