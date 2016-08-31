#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include <vector>
#include <assert.h>
#include "ihandevaluator.h"
#include "card.h"
#include "gamingtableconfiguration.h"
#include "possibletableevaluator.h"
#include "player.h"

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);
    explicit TexasHoldemModel(IHandEvaluator* evalator, QObject *parent = 0);

    void stepGame(TexasHoldem::desecition activePlayerDecesion, int activePlayerBet);
    void startRound();
    void addCommunityCards(const std::list<card>& cards);
    void setWorkerThreadNumber(int n) {_possEvalator->setNofWorkerThread(n);}

    ~TexasHoldemModel();

signals:
    void activePlayerChanged(int newNumber);
    void newGameStarted(std::vector<Player> state);
    void endGame();
    void startBidding(int nextPlayer);
    void waitingCommunityCards();
    void roundStarted();
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
                                           int activePlayerBet, const Player &activePlayerState);
    int claclulateOptimalAmount();
    int totalPot() {return _gameState.getPot() + _tableSumMoney;}
    bool analyizePlayer(Player player,int toCallAmount);

    TexasHoldem::desecition preFlopStaregy();
    TexasHoldem::desecition beforeBetStartegy();
    TexasHoldem::desecition afterBetStaregy();
    double calculateOutChance();
    void flopWinChance();
    void turnWinChance();
    void riverWinChance();


    TexasHoldem::desecition evaluateChance(double);

    GamingTableConfiguration _gameState;
    IHandEvaluator* _evalator;
    PossibleTableEvaluator* _possEvalator;


    int _minimumBet;
    int smallBlindBet;

    int flopRaise;
    int afterFlopRaise;

    std::vector<Player> _playersState;
    int nOfStartedPlayer;
    int playerNumber;



    TexasHoldem::round _round;

    bool _beforeBet;
    int _currentPlayer;
    int _tableSumMoney;
    int _nOfRaises;
    int _nOfActivePlayers;
    int _roundStarterPlayer;
    int _allMoney;

    double winChance;



};

#endif // TEXASHOLDEMMODEL_H
