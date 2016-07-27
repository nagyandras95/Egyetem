#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "handevaluator.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    _evalator = new HandEvaluator();
}


TexasHoldemModel::~TexasHoldemModel()
{
    delete _evalator;
}

GamingTableConfiguration::options TexasHoldemModel::evaluate()
{

    size_t size = _gameState.getCommunityCards().size();
    double winChance;
    if(size > 0)
    {
        double currentHandValue = _evalator->evaluate_hand(_gameState.getHiddenCards(),_gameState.getCommunityCards(),_gameState.getYourHand(),_gameState.getNOfActivePlayers());
        if(size < 5)
        {
            double chance = 0;
            {

                for(std::vector<card> poss : _gameState.getPossibleNextRoundComminityCards())
                {
                    double poss_rank_hand_value = _evalator->evaluate_hand(_gameState.getHiddenCards(),poss,_gameState.getYourHand(),_gameState.getNOfActivePlayers());
                    chance += (poss_rank_hand_value * 1 / _gameState.getHiddenCards().size());

                }
            }
            if(size == 3)
            {
                winChance = 1 - ((1 - currentHandValue) * (1-chance)*(1-chance));
            }
            else if(size == 4)
            {
                winChance =  1 - (1 - currentHandValue)*(1 - chance);
            }





            return evaluateChance(chance);
        }
        else
        {
            winChance = currentHandValue;
        }

    }
    else
    {
        double pair_value = _evalator->evaluate_pair(_gameState.getYourHand(),_gameState.getHiddenCards());
    }

    double expectedMoney = winChance*_gameState.getPot();

    if(expectedMoney < _gameState.getYourBet())
        return GamingTableConfiguration::options::fold;
    else if( expectedMoney < _gameState.getYourBet()*2)
        return GamingTableConfiguration::options::call;
    else
        return GamingTableConfiguration::options::raise;



}

GamingTableConfiguration::options TexasHoldemModel::evaluateChance(double c)
{
    if(c < 0.1)
        return GamingTableConfiguration::options::fold;
    else if(c < 0.5)
        return GamingTableConfiguration::options::call;
    else
        return GamingTableConfiguration::options::raise;

}
