#ifndef PAIR_H
#define PAIR_H

#include <algorithm>

#include "card.h"
#include "holdemtypes.h"

namespace Model
{

class Pair
{
public:
    Pair(Card card1_, Card card2_);
    Card getFirstCard() const {return card1;}
    Card getSecondCard() const {return card2;}

    int getValue() const {return value;}

private:

    void calcValue();
    int score(Card);

    Card card1;
    Card card2;

    int value;

};


inline bool operator<(const Model::Pair p1, const Model::Pair p2) {return p1.getValue() < p2.getValue();}
inline bool operator>(const Model::Pair p1, const Model::Pair p2){return p2 < p1;}
inline bool operator==(const Model::Pair p1, const Model::Pair p2){return !(p1 < p2) && !(p1 > p2);}
inline bool operator<=(const Model::Pair p1, const Model::Pair p2){return !(p1 > p2);}
inline bool operator>=(const Model::Pair p1, const Model::Pair p2){return !(p1 < p2);}
}
#endif // PAIR_H
