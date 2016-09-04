#include "cardvaluematcher.h"

CardValueMatcher::CardValueMatcher() {}

void CardValueMatcher::implementInit()
{
    for(int i = 2; i <= 10; ++i)
    {
        _matchingMap[i] = QString(std::to_string(i).c_str());
    }

    _matchingMap[11] = "B";
    _matchingMap[12] = "D";
    _matchingMap[13] = "K";
    _matchingMap[14] = "A";

}