#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <list>
#include "ihand_evaluator.h"
#include "card.h"

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    ~TexasHoldemModel();

    void set_your_cards(card c1,card c2) {game_state.your_card1 = c1; game_state.your_card2 = c2;}
    void set_community_cards(std::list<card> cards) {game_state.community_cards = cards;}
    double evaluate() {evalator->set_state(game_state); return evalator->evaluate_hand();}

signals:

public slots:

private:
    game_configuration game_state;
    Ihand_evaluator* evalator;


};

#endif // TEXASHOLDEMMODEL_H
