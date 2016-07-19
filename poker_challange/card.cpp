#include "card.h"

card::card(){}
card::card(int number_,color color_) : _number(number_),_color(color_) {}

card &card::operator=(const card &c){
    if(this != &c)
    {
        copy(c);
    }

    return *this;
}

int card::get_number() const {return _number;}

color card::get_color() const {return _color;}

void card::copy(const card &c)
{
    _number = c.get_number();
    _color = c.get_color();
}
