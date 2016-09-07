#ifndef HOLDEMTYPES_H
#define HOLDEMTYPES_H

namespace TexasHoldem
{
    enum desecition {none, fold, check, call, bet, raise, all_in};
    enum round {pre_flop, flop, turn, river};
    enum color {clubs, diamonds, hearts, spades};

    typedef int CardValueType;

    extern int MAX_VALUE;
    extern int PAIR_VALUE;
    extern int TWO_PAIR_VALUE;
    extern int DRILL_VALUE;
    extern int STRAIGHT_VALUE;
    extern int FLUSH_VALUE;
    extern int FULL_HOUSE_VALUE;
    extern int POKER_VALUE;
    extern int STARTIGHT_FLUSH_VALUE;

    extern int POSS_STARIGHT_HAND;
    extern int SAME_COLOR_HAND;
    extern int PAIR_HAND;

}

#endif // HOLDEMTYPES_H
