#ifndef CARDVALUEMATCHER_H
#define CARDVALUEMATCHER_H

#include "modelviewmatching.h"
#include "model/holdemtypes.h"


class CardValueMatcher : public ModelViewMatching<TexasHoldem::CardValueType,CardValueMatcher>
{
public:
    CardValueMatcher();
    void implementInit();

};

#endif // CARDVALUEMATCHER_H
