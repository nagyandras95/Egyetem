#include "combination.h"
#include <vector>
#include <assert.h>
#include <algorithm>
#include "holdemtypes.h"


namespace Model
{

Combination::Combination(std::vector<Card> cards_) : _cards(cards_)
{
    assert(_cards.size() == 5);
    std::sort(_cards.begin(),_cards.end());
    _value = calcValue();

    containsAice = false;
    diffSameCount = 0;

    if(containsAice && diffSameCount == 3)
    {
        calcSepcialAsceLowestStarightValue();
    }
}

int Combination::calcValue()
{
    int combSize = (int) _cards.size();
    int numberOfPairs = 0;
    bool drill = false;
    bool poker = false;
    bool straight = true;
    allSameColor = true;
    bool same;
    int countSameValues = 1;
    for(int i = 1;i < combSize; ++i)
    {

        if(_cards[i].getCardNumber() == 14 && !containsAice)
        {
            containsAice = true;
        }
        //TODO refactoring
        same = _cards[i-1].getCardNumber() == _cards[i].getCardNumber();
        int prevCount = countSameValues;
        allSameColor = allSameColor && _cards[i-1].getColor() == _cards[i].getColor();
        same ? countSameValues++ : countSameValues = 1;

        if(prevCount == 2 && countSameValues == 1)
            _criticalCards.push_back(_cards[i-1].getCardNumber());
        else if(countSameValues == 3)
            _criticalCards.push_back(_cards[i-1].getCardNumber() + TexasHoldem::MAX_VALUE);
        else if(countSameValues == 1 && prevCount == 1)
        {
            _secondaryCards.push_back(_cards[i-1].getCardNumber());
            _criticalSecondaryUnion.push_back(_cards[i-1].getCardNumber());
        }

        if(i == (combSize - 1))
        {
            if(countSameValues == 1)
            {
                _secondaryCards.push_back(_cards[i].getCardNumber());
                _criticalSecondaryUnion.push_back(_cards[i].getCardNumber());
            }

            else if(countSameValues == 2)
                _criticalCards.push_back(_cards[i].getCardNumber());

        }

        numberOfPairs = countSameValues == 2 ? numberOfPairs + 1 : numberOfPairs;
        drill = drill || countSameValues == 3;
        poker = poker || countSameValues == 4;
        straight = straight && ( (_cards[i].getCardNumber() - _cards[i-1].getCardNumber()) == 1);
        if((_cards[i].getCardNumber() - _cards[i-1].getCardNumber()) == 1)
        {
            diffSameCount++;
        }

    }

    if(allSameColor || straight)
    {
        _criticalSecondaryUnion.clear();
        for(Card c : _cards)
        {
            _criticalSecondaryUnion.push_back(c.getCardNumber());
        }


    }
    else
    {
        for(int val : _criticalCards)
            _criticalSecondaryUnion.push_back(val);
    }


    if(numberOfPairs != 0 && !drill && !poker && !allSameColor)
    {
        if(numberOfPairs == 1)
            return TexasHoldem::PAIR_VALUE;
        else
            return TexasHoldem::TWO_PAIR_VALUE;
    }
    else if(drill && !poker && !allSameColor && numberOfPairs == 1)
        return TexasHoldem::DRILL_VALUE;
    else if(allSameColor && !straight)
        return TexasHoldem::FLUSH_VALUE;
    else if(poker)
        return TexasHoldem::POKER_VALUE;
    else if(numberOfPairs == 2 && drill)
        return TexasHoldem::FULL_HOUSE_VALUE;
    else if(straight && !allSameColor)
        return TexasHoldem::STRAIGHT_VALUE;
    else if(allSameColor && straight)
        return TexasHoldem::STARTIGHT_FLUSH_VALUE;
    else
    {
        return 0;
    }

}

void Combination::calcSepcialAsceLowestStarightValue()
{

    _criticalSecondaryUnion.clear();
    if(allSameColor)
    {
        _value = TexasHoldem::STARTIGHT_FLUSH_VALUE;
    }

    for(int i = 1; i <= 5; ++i)
    {
        _criticalSecondaryUnion.push_back(i);
    }
}



bool sameCombinationIsBetter(const std::vector<int>& cards1, const std::vector<int>& cards2)
{

    assert(cards1.size() == cards2.size());
    bool l = false;
    bool gr = false;
    for(int i = (int)cards1.size() - 1; i >= 0  && !l; i--)
    {
        l = cards2[i] != cards1[i];
        gr = cards2[i] > cards1[i];
    }

    return gr;
}

bool operator<(const Model::Combination c1, const Model::Combination c2)
{
    int val1 = c1.getValue();
    int val2 = c2.getValue();
    if(val1 != val2)
    {
        return val1 < val2;
    }
    else
    {
        if(c1.getNofCards() != c2.getNofCards()) return c1.getNofCards() < c2.getNofCards();
        return sameCombinationIsBetter(c1.getDecisiveCards(),c2.getDecisiveCards());


    }
}
}
