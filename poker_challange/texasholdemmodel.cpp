#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "hand_evaluator.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    evalator = new hand_evaluator();
}


TexasHoldemModel::~TexasHoldemModel()
{
    delete evalator;
}

game_configuration::options TexasHoldemModel::evaluate()
{

    if(game_state.get_community_cards().size() > 0)
    {
        double current_hand_value = evalator->evaluate_hand(game_state.get_hidden_cards(),game_state.get_community_cards(),game_state.get_your_pair());
        if(game_state.get_community_cards().size() > 5)
        {
            double chance = 0;

            {

                for(std::vector<card> poss : game_state.get_possible_next_round_community_cards())
                {
                    double poss_rank_hand_value = evalator->evaluate_hand(game_state.get_hidden_cards(),poss,game_state.get_your_pair());
                    chance += (poss_rank_hand_value * 1 / game_state.get_hidden_cards().size());

                }
            }
        }

    }
    else
    {
        assert(game_state.get_community_cards().size() == 0);
        evalator->evaluate_pair(game_state.get_your_pair());
    }



}
