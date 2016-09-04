#include "decesionmatcher.h"

DecesionMatcher::DecesionMatcher() {}

void DecesionMatcher::implementInit()
{
    _matchingMap[TexasHoldem::none] = "";
    _matchingMap[TexasHoldem::fold] = "Fold";
    _matchingMap[TexasHoldem::call] = "Call";
    _matchingMap[TexasHoldem::check] = "Check";
    _matchingMap[TexasHoldem::bet] = "Bet";
    _matchingMap[TexasHoldem::raise] = "Raise";
}
