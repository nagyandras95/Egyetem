#include "pair.h"

pair::pair(card card1_, card card2_) : card1(card1_), card2(card2_)
{
    calcValue();
}


//ChenFormula
void pair::calcValue()
{
    value = std::max(score(card1),score(card2));

    int diff = std::abs(card1.get_number() - card2.get_number());
    switch(diff)
    {
    case 0 : value = std::max(5,value*2); break;
    case 1 : value++; break;
    case 2 : value--; break;
    case 3 : value = value - 2; break;
    case 4: value = value - 4; break;
    default: value = value - 5; break;
    }

    if(card1.get_color() == card2.get_color())
    {
        value += 2;
    }

    value = value - diff;
}

int pair::score(card c)
{
    switch (c.get_number()) {
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
        return c.get_number() / 2;
    }
}
