#ifndef PAIR_H
#define PAIR_H

#include <algorithm>

#include "card.h"
#include "holdemtypes.h"

class pair
{
public:
    pair(card card1_, card card2_);

    int getValue() const {return value;}

private:

    void calcValue();

    card card1;
    card card2;

    int value;

};

inline bool operator<(const pair p1, const pair p2) {return p1.getValue() < p2.getValue();}
inline bool operator>(const pair p1, const pair p2){return p2 < p1;}
inline bool operator==(const pair p1, const pair p2){return !(p1 < p2) && !(p1 > p2);}
inline bool operator<=(const pair p1, const pair p2){return !(p1 > p2);}
inline bool operator>=(const pair p1, const pair p2){return !(p1 < p2);}

#endif // PAIR_H
