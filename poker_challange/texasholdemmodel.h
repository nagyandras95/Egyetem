#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <vector>
#include "ihand_evaluator.h"
#include "card.h"

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    ~TexasHoldemModel();

    void setYourCards(card c1,card c2) {_gameState.your_card1 = c1; _gameState.your_card2 = c2;}
    void setCommunityCards(const std::vector<card> cards) {_gameState.community_cards = cards;}
    void setNOfPlayers(int n) {_gameState.number_of_all_players = n;}
    void setYourBet(int n) {_gameState.your_bet = n;}
    void setTotalPot(int n) {_gameState.full_bet_amount = n;}

    GamingTableConfiguration::options evaluate();

signals:

public slots:

private:

    GamingTableConfiguration::options evaluateChance(double);

    GamingTableConfiguration _gameState;
    IHandEvaluator* _evalator;


};

#endif // TEXASHOLDEMMODEL_H
