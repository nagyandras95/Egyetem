#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <vector>
#include <assert.h>
#include "ihandevaluator.h"
#include "card.h"
#include "gamingtableconfiguration.h"
#include "possibletableevaluator.h"


struct PlayerRoundState {

    PlayerRoundState( TexasHoldem::desecition lastDesecition_ = TexasHoldem::none, int bet_= 0):
     lastDesecition(lastDesecition_), bet(bet_), nOfRaises(0)  {}

    TexasHoldem::desecition lastDesecition;
    int nOfRaises;
    int bet;
};

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    explicit TexasHoldemModel(IHandEvaluator* evalator, QObject *parent = 0);

    void stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet);
    void startRound();
    void addCommunityCards(const std::list<card>& cards);

    ~TexasHoldemModel();

signals:
    void activePlayerChanged(int newNumber);
    void newGameStarted(std::vector<PlayerRoundState> state);
    void endGame();
    void startBidding(int nextPlayer);
    void waitingYourHand();
    void waitingCommunityCards();
    void selectCommunityCards(int from,int to);
    void nextRoundStarted(int currentPlayer);
    void choiceOptionsChanged(bool beforeBet);

    void potChanged(int pot);
    void nOfActivePlayerChanged(int players);
    void yourBetChanged(int yourBet);

    void nextPlayerHint();

    void invalidState(QString message);


public slots:
    TexasHoldem::desecition evaluate();

    void startGame(int players_, int smallBlindBet_, int bigBlindBet_, int playerNumber_);

    void setYourCards(const card& c1,const card& c2) {_gameState.setYourHand(c1,c2);}
    void setCommunityCards(const std::vector<card> cards) {_gameState.setCommunityCards(cards);}
    void setNOfPlayers(int n) {_gameState.setNOfActivePlayers(n);}
    void setYourBet(int n) {_gameState.setYourBet(n);}
    void setTotalPot(int n) {_gameState.setPot(n);}

private:

    int searchNextAtivePlayer();
    int serachFirstActivePlayer();
    void nextRound();
    std::pair<bool, QString> validateState(TexasHoldem::desecition activePlayerDecesion,
                                           int activePlayerBet, const PlayerRoundState &activePlayerState);

    TexasHoldem::desecition evaluateChance(double);

    GamingTableConfiguration _gameState;
    IHandEvaluator* _evalator;
    PossibleTableEvaluator* _possEvalator;


    int _minimumBet;
    int smallBlindBet;

    std::vector<PlayerRoundState> _playersState;
    int nOfStartedPlayer;
    int playerNumber;

    TexasHoldem::round _round;

    bool _beforeBet;
    int _currentPlayer;
    int _tableSumMoney;
    int _nOfRaises;
    int _nOfActivePlayers;
    int _roundStarterPlayer;



};

#endif // TEXASHOLDEMMODEL_H
