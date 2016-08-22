#include "pair.h"

pair::pair(card card1_, card card2_) : card1(card1_), card2(card2_)
{
    calcValue();
}

void pair::calcValue()
{
    bool n_same = false, c_same = false, poss_staright = false;
    n_same = card1.get_number() == card2.get_number();
    c_same = card1.get_color() == card2.get_color();
    poss_staright = std::abs(card1.get_number() - card2.get_number()) <= 4 && !n_same;

    value = poss_staright*TexasHoldem::POSS_STARIGHT_HAND +
            c_same*TexasHoldem::SAME_COLOR_HAND +
            n_same*TexasHoldem::PAIR_HAND +
            std::max(card1,card2).get_number() +
            std::min(card1,card2).get_number();
}
