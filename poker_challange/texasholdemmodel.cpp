#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    evalator.game_state.your_card1 = card(13,color::clubs);
    evalator.game_state.your_card2 = card(14,color::clubs);
    std::list<card> comm;
    comm.push_back(card(12,color::clubs));
    comm.push_back(card(11,color::clubs));
    comm.push_back(card(10,color::clubs));
    evalator.game_state.community_cards = comm;
    qDebug() << evalator.evaluate_hand();
    qDebug() << evalator.evaluate_hand();
}
