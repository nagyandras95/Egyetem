#include "strageist.h"
#include "handevaluator.h"

namespace Model
{

Strageist::Strageist(const GamingTableConfiguration &state_) : _gameState(state_),
    _evalator(new HandEvaluator), _possEvalator(new PossibleTableEvaluator(state_)) {}

TexasHoldem::desecition Strageist::evaluate()
{
    if(_gameState.getRound() == TexasHoldem::pre_flop)
    {
        return preFlopStaregy();
    }
    else if(_gameState.getRound() == TexasHoldem::flop)
    {
        calculateFlopWinChance();
    }
    else if(_gameState.getRound() == TexasHoldem::turn)
    {
        calculateTurnWinChance();
    }
    else //river
    {
        calculateRiverWinChance();
    }

    if(_gameState.isBeforeBet())
    {
        return beforeBetStartegy();

    }
    else
    {

        return afterBetStaregy();
    }
}

TexasHoldem::desecition Strageist::preFlopStaregy()
{
    _winChance = _evalator->evaluatePair(_gameState.getYourHand(),_gameState.getHiddenCards());
    /*
                             * In the pre-flop we does not have any investment
                             * so the logic is very simple: only realy strong hand should be played.
                            */
    if(_winChance < 0.9)
    {
        if((_gameState.playerIsBigBlind() && _gameState.getRaises() > 0 && _winChance > 0.8) ||
                (_gameState.playerIsBigBlind() && _gameState.getRaises() == 0))
        {
            return TexasHoldem::call;
        }
        else
        {
            return TexasHoldem::fold;
        }
    }
    else if(_winChance > 0.98)
    {
        return TexasHoldem::raise;
    }
    else if(_winChance > 0.95)
    {
        if(_gameState.getRaises() == 0)
        {
            return TexasHoldem::raise;
        }
        else
        {
            return TexasHoldem::call;
        }
    }
    else
    {
        if(_gameState.getRaises() == 0)
        {
            return TexasHoldem::call;
        }
        else
        {
            return TexasHoldem::fold;
        }
    }
}

TexasHoldem::desecition Strageist::beforeBetStartegy()
{
    if(_winChance*(_gameState.getTotalPot()) < _gameState.getYourBet())
    {
        return TexasHoldem::check;
    }
    else
    {
        return TexasHoldem::bet;
    }
}

TexasHoldem::desecition Strageist::afterBetStaregy()
{
    double expectedMoney = _winChance*(_gameState.getTotalPot() + (_gameState.getMinimumBet() - _gameState.getThePlayerState().bet));
    /*
     * If the expected money less then the already invested and should be
     * invested money in tis situtaion
     * it does not worth to call it.
    */
    if(expectedMoney < (_gameState.getYourBet() + (_gameState.getMinimumBet() - _gameState.getThePlayerState().bet)))
    {
        return TexasHoldem::fold;
    }
    else
    {
        /*
         * We should consider what the optimal decesion is: call or raise.
         * Our gone to maximase our profit, for that we should consider our and opponents chances..
        */

        int afterRisePot;
        int afterRaiseInvest;
        if(_gameState.getRound() == TexasHoldem::flop)
        {
            afterRisePot = _gameState.getTotalPot() + (_gameState.getMinimumBet() +
                           _gameState.getRaiseAmount() - _gameState.getThePlayerState().bet);
            afterRaiseInvest = _gameState.getYourBet() + (_gameState.getMinimumBet() +
                               _gameState.getRaiseAmount() - _gameState.getThePlayerState().bet);
        }

        expectedMoney = _winChance*(afterRisePot);
        if(expectedMoney < afterRaiseInvest)
        {
            return TexasHoldem::call;
        }
        else if(_gameState.getRaises() == 0)
        {
            return TexasHoldem::raise;
        }
        else
        {
            return analyzeBestOption();
        }

    }
}

TexasHoldem::desecition Strageist::analyzeBestOption()
{
    PossibaleState myState(_gameState.getTotalPot(),_gameState.getMinimumBet(),_gameState.getPlayerPosition(),
                           _gameState.getRaises(),_gameState.getCalls(),1);
    std::list<PossibaleState> startingStates = getStateChildren(myState);
    PossibaleState callState = startingStates.front();
    PossibaleState raiseState = startingStates.back();

    double callExpectedMoney = analyzeBranch(callState);
    double raiseExpectedMoney = analyzeBranch(raiseState);
    if(callExpectedMoney < raiseExpectedMoney && (raiseExpectedMoney - callExpectedMoney) > getAdditionInvest(_gameState.getPlayerPosition(),_gameState.getMinimumBet(),TexasHoldem::raise))
    {
        return TexasHoldem::raise;
    }
    else
    {
        return TexasHoldem::call;
    }


}

double Strageist::calculateOutChance()
{
    _possEvalator->evalauteChance();
    return _possEvalator->getChance();
}

void Strageist::calculateFlopWinChance()
{
    double chance = calculateOutChance();
    _winChance = 1 - (1-chance)*(1-chance);
}

void Strageist::calculateTurnWinChance()
{
    _winChance = calculateOutChance();

}

void Strageist::calculateRiverWinChance()
{
    _winChance = _evalator->evaluateHand(_gameState.getHiddenCards(),_gameState.getCommunityCards(),
                                         _gameState.getYourHand(),_gameState.getNOfActivePlayers());
}


double Strageist::analyzeBranch(const PossibaleState &root)
{
    double expectedMoney = 0;
    int countLeaf = 0;
    std::queue<PossibaleState,std::list<PossibaleState> > stateQueue(getStateChildren(root));
    while(!stateQueue.empty())
    {
        PossibaleState state = stateQueue.front();
        stateQueue.pop();
        std::list<PossibaleState> children = getStateChildren(state);
        for(PossibaleState child : children)
        {
            stateQueue.push(child);
        }
        if(children.empty())
        {
            expectedMoney += state.chance * state.pot;
            countLeaf++;
        }
    }
    return expectedMoney / countLeaf;
}

std::list<PossibaleState> Strageist::getStateChildren(PossibaleState state)
{
    std::list<PossibaleState> childen;

    int next = _gameState.searchNextAtivePlayer(state.playerPosition);
    if(!_gameState.isRoundStarter(state.playerPosition))
    {
        int callInvest = getAdditionInvest(state.playerPosition,state.minimumCall,TexasHoldem::call);
        int raiseInvest = getAdditionInvest(state.playerPosition,state.minimumCall,TexasHoldem::raise);

        int callPot = state.pot + callInvest;
        int raisePot = state.pot + raiseInvest;
        double callChance = 1 - ((double) (_gameState.getPositionedPlayer(state.playerPosition).allBet + callInvest) / callPot) -
                ((double) 0.02*_gameState.getCalls() + 0.1*_gameState.getRaises());
        double foldChance = 1 - callChance;
        double raiseChance = (1 - ((double) (_gameState.getPositionedPlayer(state.playerPosition).allBet + raiseInvest) / raisePot) -
                ((double) 0.04*_gameState.getCalls() + 0.2* (_gameState.getRaises()))) * ( ((double)_gameState.positionDiffRelatedToStarter(state.playerPosition) - 1) / _gameState.getNOfActivePlayers());
        if(state.playerPosition == _gameState.getPlayerPosition())
        {
            callChance = 1;
            raiseChance = 1;
        }
        childen.push_back(PossibaleState(callPot,state.minimumCall,next,state.nOfRaises,state.nOfCalls + 1, state.chance*callChance));
        childen.push_back(PossibaleState(raisePot,state.minimumCall+_gameState.getRaiseAmount(),next,state.nOfRaises + 1,state.nOfCalls,state.chance*raiseChance));


        if(state.playerPosition != _gameState.getPlayerPosition())
        {
            childen.push_back(PossibaleState(state.pot,state.minimumCall,next,state.nOfRaises,state.nOfCalls,state.chance*foldChance));
        }
    }

    return childen;


}

int Strageist::getAdditionInvest(int playerPosition, int minCall, TexasHoldem::desecition dec)
{
    assert(dec == TexasHoldem::raise || dec == TexasHoldem::call);
    if(dec == TexasHoldem::call)
    {
        return minCall - _gameState.getPositionedPlayer(playerPosition).bet;
    }
    else
    {
        return minCall + _gameState.getRaiseAmount() - _gameState.getPositionedPlayer(playerPosition).bet;
    }
}

}
