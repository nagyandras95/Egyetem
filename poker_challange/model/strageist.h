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
    std::pair<TexasHoldem::desecition,int> evaluate();
    void initCalulcatorState() {_winChanceCalulated = false;}

private:
    std::pair<TexasHoldem::desecition,int> preFlopStaregy();
    std::pair<TexasHoldem::desecition,int> beforeBetStartegy();
    std::pair<TexasHoldem::desecition,int> afterBetStaregy();
    double calculateOutChance();
    void calculateFlopWinChance();
    void calculateTurnWinChance();
    void calculateRiverWinChance();

    int getAdditionInvest(int playerPosition, int minCall, TexasHoldem::desecition dec);
    std::pair<TexasHoldem::desecition,int> raise() {return std::pair<TexasHoldem::desecition,int>(TexasHoldem::raise,_gameState.getMinimumBet() + _gameState.getRaiseAmount());}
    std::pair<TexasHoldem::desecition,int> call() {return std::pair<TexasHoldem::desecition,int>(TexasHoldem::call,_gameState.getMinimumBet());}
    std::pair<TexasHoldem::desecition,int> fold() {return std::pair<TexasHoldem::desecition,int>(TexasHoldem::fold,0);}
    std::pair<TexasHoldem::desecition,int> check() {return std::pair<TexasHoldem::desecition,int>(TexasHoldem::check,0);}
    std::pair<TexasHoldem::desecition,int> bet() {return std::pair<TexasHoldem::desecition,int>(TexasHoldem::bet,_gameState.getRaiseAmount());}



    std::pair<TexasHoldem::desecition,int> analyzeBestOption();
    std::list<PossibaleState> getStateChildren(PossibaleState state);
    double analyzeBranch(const PossibaleState& root);

    const GamingTableConfiguration& _gameState;

    IHandEvaluator* _evalator;
    PossibleTableEvaluator* _possEvalator;

    double _winChance;
    bool _winChanceCalulated;
};
}




#endif // STRAGEIST_H
