#ifndef EVENTI_HPP_INCLUDED
#define EVENTI_HPP_INCLUDED

#include "runtimetypes.hpp"
#include <atomic>
class StateMachineI;

struct IEvent
{
  IEvent () {}
  virtual ~IEvent () {}
  virtual void setPortType (int) = 0;
  
};

struct EventBase
{
  EventBase (int t_) : t (t_), p (NoPort_PE) {}
	
  int t;
  std::atomic_int p;
};

typedef const EventBase& EventBaseCRef;

#endif // EVENTI_HPP_INCLUDED
