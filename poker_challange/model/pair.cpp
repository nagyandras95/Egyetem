#include "pair.h"

namespace Model
{
Pair::Pair(Card card1_, Card card2_) : card1(card1_), card2(card2_)
{
    calcValue();
}

/*
 * Calculate streight of pair by ChenFormula.
 * It determinates an integer for a Pair.
 */
void Pair::calcValue()
{
    value = std::max(score(card1),score(card2));

    int diff = std::abs(card1.getCardNumber() - card2.getCardNumber());
    switch(diff)
    {
    case 0 : value = std::max(5,value*2); break;
    case 1 : value++; break;
    case 2 : value--; break;
    case 3 : value = value - 2; break;
    case 4: value = value - 4; break;
    default: value = value - 5; break;
    }

    if(card1.getColor() == card2.getColor())
    {
        value += 2;
    }

    value = value - diff;
}

int Pair::score(Card c)
{
    switch (c.getCardNumber()) {
    case 14:
        return 10;
        break;
    case 13:
        return 8;
    case 12:
        return 7;
    case 11:
        return 6;
    default:
        return c.getCardNumber() / 2;
    }
}
}


