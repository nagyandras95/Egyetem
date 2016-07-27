#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <vector>
#include "ihandevaluator.h"
#include "card.h"
#include "gamingtableconfiguration.h"

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    TexasHoldemModel(IHandEvaluator* evalator, QObject *parent = 0);
    ~TexasHoldemModel();

    void setYourCards(const card& c1,const card& c2) {_gameState.setYourHand(c1,c2);}
    void setCommunityCards(const std::vector<card> cards) {_gameState.setCommunityCards(cards);}
    void setNOfPlayers(int n) {_gameState.setNOfActivePlayers(n);}
    void setYourBet(int n) {_gameState.setYourBet(n);}
    void setTotalPot(int n) {_gameState.setPot(n);}

    GamingTableConfiguration::options evaluate();

signals:

public slots:

private:

    GamingTableConfiguration::options evaluateChance(double);

    GamingTableConfiguration _gameState;
    IHandEvaluator* _evalator;


};

#endif // TEXASHOLDEMMODEL_H
