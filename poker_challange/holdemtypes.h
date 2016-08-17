#ifndef HOLDEMTYPES_H
#define HOLDEMTYPES_H

namespace TexasHoldem
{
    enum desecition {none, fold, check, call, bet, raise};
    enum round {pre_flop, flop, turn, river};

    extern int MAX_VALUE;
    extern int PAIR_VALUE;
    extern int TWO_PAIR_VALUE;
    extern int DRILL_VALUE;
    extern int STRAIGHT_VALUE;
    extern int FLUSH_VALUE;
    extern int FULL_HOUSE_VALUE;
    extern int POKER_VALUE;
    extern int STARTIGHT_FLUSH_VALUE;

}

#endif // HOLDEMTYPES_H
