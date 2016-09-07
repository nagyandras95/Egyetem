#ifndef STRAGEIST_H
#define STRAGEIST_H

#include <list>
#include "model/holdemtypes.h"
#include "model/gamingtableconfiguration.h"
#include "possiblestate.h"
#include "possibletableevaluator.h"
#include "ihandevaluator.h"
#include "holdemtypes.h"

namespace Model
{
class Strageist
{
public:
    Strageist(const GamingTableConfiguration& state_);
    void setNOfWorkerThreads(int n) {_possEvalator->setNofWorkerThread(n);}
    TexasHoldem::desecition evaluate();

private:
    TexasHoldem::desecition preFlopStaregy();
    TexasHoldem::desecition beforeBetStartegy();
    TexasHoldem::desecition afterBetStaregy();
    double calculateOutChance();
    void calculateFlopWinChance();
    void calculateTurnWinChance();
    void calculateRiverWinChance();

    int getAdditionInvest(int playerPosition, int minCall, TexasHoldem::desecition dec);

    TexasHoldem::desecition analyzeBestOption();
    std::list<PossibaleState> getStateChildren(PossibaleState state);
    double analyzeBranch(const PossibaleState& root);

    const GamingTableConfiguration& _gameState;

    IHandEvaluator* _evalator;
    PossibleTableEvaluator* _possEvalator;

    double _winChance;
};
}




#endif // STRAGEIST_H
