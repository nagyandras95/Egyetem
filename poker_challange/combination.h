#ifndef COMBINATION_H
#define COMBINATION_H
#include "card.h"
#include <list>
#include <vector>
#include <assert.h>
#include <algorithm>

std::pair<bool,bool> is_better(std::vector<int>&,std::vector<int>&);


class combination
{
public:
    combination(std::list<card> comb);

    int calc_value();
    int get_value() const {return value;}
    int get_nof_cards() const {return (int) cards.size();}

    const std::vector<int>& get_decisive_cards() const {return ctiric_second_uinon;}


    static int MAX_VALUE;
    static int PAIR_VALUE;
    static int DRILL_VALUE;
    static int STRAIGHT_VALUE;
    static int FLUSH_VALUE;
    static int FULL_HOUSE_VALUE;
    static int POKER_VALUE;
    static int STARTIGHT_FLUSH_VALUE;

private:
   std::list<card> cards;
   int value;

   std::vector<int> critical_cards;
   std::vector<int> secondary_cards;
   std::vector<int> ctiric_second_uinon;







};



bool operator<(const combination, const combination);
inline bool operator>(const combination c1, const combination c2){return c2 < c1;}
inline bool operator==(const combination c1, const combination c2){return !(c1 < c2) && !(c1 > c2);}
inline bool operator<=(const combination c1, const combination c2){return !(c1 > c2);}
inline bool operator>=(const combination c1, const combination c2){return !(c1 < c2);}

#endif // COMBINATION_H
