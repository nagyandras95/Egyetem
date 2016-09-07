#include "cardcolormatcher.h"
#include "holdemtypes.h"

CardColorMatcher::CardColorMatcher() {}

void CardColorMatcher::implementInit()
{
    _matchingMap[TexasHoldem::clubs] = "Clubs";
    _matchingMap[TexasHoldem::diamonds] = "Diamonds";
    _matchingMap[TexasHoldem::hearts] = "Hearts";
    _matchingMap[TexasHoldem::spades] = "Spades";
}
