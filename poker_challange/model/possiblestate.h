#ifndef POSSIBLESTATE
#define POSSIBLESTATE


struct PossibaleState
{
    PossibaleState(int pot_, int minimum_, int playerPosition_,int nOfRaises_,int nOfCalls_, double chance_) :
        pot(pot_), minimumCall(minimum_),playerPosition(playerPosition_),
        nOfRaises(nOfRaises_), nOfCalls(nOfCalls_), chance(chance_) {}
    int pot;
    int minimumCall;
    int playerPosition;
    int nOfRaises;
    int nOfCalls;
    double chance;
};

#endif // POSSIBLESTATE

