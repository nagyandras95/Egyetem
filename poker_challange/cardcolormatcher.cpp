#include "cardcolormatcher.h"

CardColorMatcher::CardColorMatcher() {}

void CardColorMatcher::implementInit()
{
    _matchingMap[card::color::clubs] = "Clubs";
    _matchingMap[card::color::diamonds] = "Diamonds";
    _matchingMap[card::color::hearts] = "Hearts";
    _matchingMap[card::color::spades] = "Spades";
}
