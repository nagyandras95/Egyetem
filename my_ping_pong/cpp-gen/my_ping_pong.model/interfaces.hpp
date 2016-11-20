#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "runtime/ievent.hpp"
class PingPongInf : public IEvent
{
public:
PingPongInf () {}
};

class OtherInf : public IEvent
{
public:
OtherInf () {}
};

#endif
