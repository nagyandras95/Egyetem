#ifndef POSSIBLETABLEEVALUATOR_H
#define POSSIBLETABLEEVALUATOR_H


#include "ihandevaluator.h"
#include "threadsafequeue.h"
#include "card.h"
#include <list>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

class PossibleTableEvaluator
{
public:
    PossibleTableEvaluator();

    void evalauteChance();
    double getChance() {return _chance;}

    void setPair(const std::pair<card,card> p) {_pair = p;}
    void setNOfPlayers(const int p) {_players = p;}
    void setUnknownCards(const std::list<card>& unknownCards) {_unknownCards = unknownCards;}
    void setCommunityCards(const std::vector<card>& communityCards) {_communityCards = communityCards;}
    void setNofWorkerThread(int n) {_nOfThrads = n;}

private:

    void task();
    void superimposeCards();

    void startQueues();

    IHandEvaluator* _evaluator;

    ThreadSafeQueue<card> _cardQueue;
    ThreadSafeQueue<double> _evalautedValueQueue;

    std::list<card> _unknownCards;
    std::vector<card> _communityCards;

    double _chance;

    std::pair<card,card> _pair;
    int _players;

    std::atomic_bool _terminated;

    int _nOfThrads = 1;
    std::vector<std::thread*> _workers;

    std::condition_variable _cond;




};

#endif // POSSIBLETABLEEVALUATOR_H
