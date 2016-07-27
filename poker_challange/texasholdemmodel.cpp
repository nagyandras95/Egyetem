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

    if(_gameState.get_community_cards().size() > 0)
    {
        double winChance;
        double current_hand_value = _evalator->evaluate_hand(_gameState.get_hidden_cards(),_gameState.get_community_cards(),_gameState.get_your_pair());
        if(_gameState.get_community_cards().size() < 5)
        {
            double chance = 0;
            {

                for(std::vector<card> poss : _gameState.get_possible_next_round_community_cards())
                {
                    double poss_rank_hand_value = _evalator->evaluate_hand(_gameState.get_hidden_cards(),poss,_gameState.get_your_pair());
                    chance += (poss_rank_hand_value * 1 / _gameState.get_hidden_cards().size());

                }
            }
            if(_gameState.get_community_cards().size() == 3)
            {
                winChance = 1 - ( (1-chance)*(1-chance));
            }
            else if(_gameState.get_community_cards().size() == 4)
            {
                winChance = chance;
            }


            //int expectedMoney = countExpectedMoney(winChance, _gameState.number_of_all_players,_gameState.full_bet_amount);


            return evaluateChance(chance);
        }
        else
        {
            winChance = current_hand_value;
            return evaluateChance(current_hand_value);
        }

    }
    else
    {
        assert(_gameState.get_community_cards().size() == 0);
        double pair_value = _evalator->evaluate_pair(_gameState.get_your_pair(),_gameState.get_hidden_cards());

        return evaluateChance(pair_value);
    }



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
