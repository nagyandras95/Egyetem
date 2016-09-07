#ifndef COMBINATION_H
#define COMBINATION_H
#include <list>
#include <vector>
#include <assert.h>
#include <algorithm>
#include "card.h"


namespace Model
{
std::pair<bool,bool> sameCombinationIsBetter(std::vector<int>&,std::vector<int>&);

class Combination
{
public:
    Combination(std::vector<Card>);

    int calcValue();
    int getValue() const {return _value;}
    int getNofCards() const {return (int) _cards.size();}

    const std::vector<int>& getDecisiveCards() const {return criticalSecondaryUnion;}


private:
   std::vector<Card> _cards;
   int _value;

   std::vector<int> criticalCards;
   std::vector<int> secondaryCards;
   std::vector<int> criticalSecondaryUnion;


};


bool operator<(const Model::Combination, const Model::Combination);
inline bool operator>(const Model::Combination c1, const Model::Combination c2){return c2 < c1;}
inline bool operator==(const Model::Combination c1, const Model::Combination c2){return !(c1 < c2) && !(c1 > c2);}
inline bool operator<=(const Model::Combination c1, const Model::Combination c2){return !(c1 > c2);}
inline bool operator>=(const Model::Combination c1, const Model::Combination c2){return !(c1 < c2);}
}
#endif // COMBINATION_H
