#ifndef CARDCOLORMATCHER_H
#define CARDCOLORMATCHER_H

#include "modelviewmatching.h"
#include "model/card.h"

class CardColorMatcher : public ModelViewMatching<card::color,CardColorMatcher>
{
public:
    CardColorMatcher();

    void implementInit();
};

#endif // CARDCOLORMATCHER_H
