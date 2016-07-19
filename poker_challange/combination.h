#ifndef COMBINATION_H
#define COMBINATION_H
#include "card.h"
#include <list>

#include <qdebug.h>

class combination
{
public:
    combination(std::list<card> comb);

    int calc_value();
    int get_value() {return value;}
    card get_max() {return max;}


private:
   std::list<card> cards;
   int value;
   card max;



   static int PAIR_VALUE;
   static int DRILL_VALUE;
   static int STRAIGHT_VALUE;
   static int FLUSH_VALUE;
   static int FULL_HOUSE_VALUE;
   static int POKER_VALUE;
   static int STARTIGHT_FLUSH_VALUE;



};



inline bool operator<(combination c1, combination c2) {return c1.get_value() < c2.get_value() ||
            (c1.get_value() == c2.get_value() && c1.get_max() < c2.get_max() );}
inline bool operator>(combination c1, combination c2){return c2 < c1;}
inline bool operator==(combination c1, combination c2){return !(c1 < c2) && !(c2 > c2);}
inline bool operator<=(combination c1, combination c2){return !(c1 > c2);}
inline bool operator>=(combination c1, combination c2){return !(c1 < c2);}

#endif // COMBINATION_H
