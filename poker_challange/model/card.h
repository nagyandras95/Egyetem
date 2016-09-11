#ifndef CARD_H
#define CARD_H

#include "holdemtypes.h"
namespace Model
{
class Card
{
public:

    Card();
    Card(int,TexasHoldem::color);
    Card(const Card&);
    Card& operator=(const Card&);
    int getCardNumber() const;
    TexasHoldem::color getColor() const;


private:

    void copy(const Card&);

    int _number;
    TexasHoldem::color _color;

};


inline bool operator<(const Model::Card c1, const Model::Card c2) {return c1.getCardNumber() < c2.getCardNumber();}
inline bool operator>(const Model::Card c1, const Model::Card c2){return c2 < c1;}
inline bool operator==(const Model::Card c1, const Model::Card c2){return c1.getCardNumber() == c2.getCardNumber() && c1.getColor() == c2.getColor();}
inline bool operator!=(const Model::Card c1, const Model::Card c2) {return !(c1 == c2);}
inline bool operator<=(const Model::Card c1, const Model::Card c2){return !(c1 > c2);}
inline bool operator>=(const Model::Card c1, const Model::Card c2){return !(c1 < c2);}

}

#endif // CARD_H
