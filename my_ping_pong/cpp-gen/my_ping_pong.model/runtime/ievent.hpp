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
  virtual int getType() = 0;
  
};

struct EventBase : public IEvent
{
  EventBase (int t_) : t (t_), p (NoPort_PE) {}
  virtual void setPortType(int pt_) {p = pt_;}
  virtual int getType() {return t;}
  int t;
  std::atomic_int p;
};

typedef const EventBase& EventBaseCRef;

#endif // EVENTI_HPP_INCLUDED
