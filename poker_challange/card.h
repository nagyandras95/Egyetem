#ifndef CARD_H
#define CARD_H


enum color {clubs, diamonds, hearts, spades};

class card
{
public:
    card();   
    card(color color_, int number_);
    card(const card& c) {copy(c);}
    card& operator=(card& c){
        if(this != &c)
        {
            copy(c);
        }

        return c;
    }


    int get_number() const {return _number;}
    color get_color() const {return _color;}


private:

    void copy(const card& c)
    {
        _number = c.get_number();
        _color = c.get_color();
    }

    color _color;
    int _number;
};

inline bool operator<(card c1, card c2) {return c1.get_number() < c2.get_number();}
inline bool operator>(card c1, card c2){return c2 < c1;}
inline bool operator==(card c1, card c2){return !(c1 < c2) && !(c2 > c2);}
inline bool operator<=(card c1, card c2){return !(c1 > c2);}
inline bool operator>=(card c1, card c2){return !(c1 < c2);}


#endif // CARD_H
