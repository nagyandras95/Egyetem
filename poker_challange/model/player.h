#ifndef PLAYER_H
#define PLAYER_H

#include "holdemtypes.h"

struct Player {

    Player( TexasHoldem::desecition lastDesecition_ = TexasHoldem::none, int bet_= 0):
     lastDesecition(lastDesecition_),nOfRaises(0),bet(bet_),allBet(0),raisePower(0),callRaisePower(0)  {}

    void addCurrentBetToAllBet() {allBet+=bet;}
    int getTotalBet() {return allBet + bet;}

    TexasHoldem::desecition lastDesecition;
    int nOfRaises;
    int powerPoints;
    int bet;
    int allBet;

    int raisePower;
    int callRaisePower;
};

#endif // PLAYER_H
