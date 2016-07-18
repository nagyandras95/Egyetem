#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <list>
#include "card.h"


struct configuration
{
    enum options {check,call,raise,fold};
    enum round {pre_flop, flop, turn, river};


    configuration()
    {
        for(int i = 2; i <= 14; i++ )
        {
            hidden_cards.push_back(card(i,color::clubs));
            hidden_cards.push_back(card(i,color::diamonds));
            hidden_cards.push_back(card(i,color::hearts));
            hidden_cards.push_back(card(i,color::spades));
        }
    }

    card your_card1;
    card your_card2;

    std::list<card> hidden_cards;
    std::list<card> community_cards;

    int number_of_all_players;
    int number_of_faied_players;

    int full_bet_amount;
    int your_bet;

    round current_round;

    bool small_bind;
    bool big_bind;
};


class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);

signals:

public slots:

private:
    configuration game_state;
    configuration::options next_hint()
    {


        return configuration::options::fold;
    }
};

#endif // TEXASHOLDEMMODEL_H
