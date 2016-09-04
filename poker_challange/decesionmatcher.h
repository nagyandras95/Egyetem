#ifndef DECESIONMATCHER_H
#define DECESIONMATCHER_H

#include "modelviewmatching.h"
#include "model/holdemtypes.h"

class DecesionMatcher : public ModelViewMatching<TexasHoldem::desecition,DecesionMatcher>
{
public:
    DecesionMatcher();
    void implementInit();
};

#endif // DECESIONMATCHER_H
