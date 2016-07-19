#ifndef CARD_H
#define CARD_H


enum color {clubs, diamonds, hearts, spades};

class card
{
public:
    card();   
    card(int number_,color color_);
    card(const card& c) {copy(c);}
    card& operator=(const card& c);
    int get_number() const;
    color get_color() const;


private:

    void copy(const card& c);

    int _number;
    color _color;

};

inline bool operator<(card c1, card c2) {return c1.get_number() < c2.get_number();}
inline bool operator>(card c1, card c2){return c2 < c1;}
inline bool operator==(card c1, card c2){return !(c1 < c2) && !(c1 > c2) && c1.get_color() == c2.get_color();}
inline bool operator!=(card c1, card c2) {return !(c1 == c2);}
inline bool operator<=(card c1, card c2){return !(c1 > c2);}
inline bool operator>=(card c1, card c2){return !(c1 < c2);}


#endif // CARD_H
