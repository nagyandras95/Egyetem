#include "card.h"

namespace Model
{
Card::Card(){}
Card::Card(int number_,TexasHoldem::color color_) : _number(number_),_color(color_) {}
Card::Card(const Card& c) {copy(c);}
Card& Card::operator=(const Card &c){
    if(this != &c)
    {
        copy(c);
    }

    return *this;
}

int Card::getCardNumber() const {return _number;}

TexasHoldem::color Card::getColor() const {return _color;}

void Card::copy(const Card& c)
{
    _number = c.getCardNumber();
    _color = c.getColor();
}
}


