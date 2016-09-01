#ifndef CARD_H
#define CARD_H




class card
{
public:
    enum color {clubs, diamonds, hearts, spades};


    card();   
    card(int,card::color);
    card(const card&);
    card& operator=(const card&);
    int get_number() const;
    card::color get_color() const;




private:

    void copy(const card&);

    int _number;
    card::color _color;

};

inline bool operator<(const card c1, const card c2) {return c1.get_number() < c2.get_number();}
inline bool operator>(const card c1, const card c2){return c2 < c1;}
inline bool operator==(const card c1, const card c2){return !(c1 < c2) && !(c1 > c2) && c1.get_color() == c2.get_color();}
inline bool operator!=(const card c1, const card c2) {return !(c1 == c2);}
inline bool operator<=(const card c1, const card c2){return !(c1 > c2);}
inline bool operator>=(const card c1, const card c2){return !(c1 < c2);}


#endif // CARD_H
