#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "runtime/ievent.hpp"
#include "interfaces.hpp"
enum Events {
	InitSignal_EE = 1, PingSignal_EE = 2, PongSignal_EE = 3, StartPlaying_EE = 4
};
struct PingSignal_EC: public EventBase, public PingPongInf, public OtherInf {
	PingSignal_EC() :
			EventBase(PingSignal_EE) {
	}
	virtual void setPortType(int type) {p = type;}

};

struct PongSignal_EC: public EventBase, public PingPongInf {
	PongSignal_EC() :
			EventBase(PongSignal_EE) {
	}
	virtual void setPortType(int type) {p = type;}
};

struct StartPlaying_EC: public IEvent, public EventBase {
	StartPlaying_EC() :
			EventBase(StartPlaying_EE) {
	}
virtual void setPortType (int type) { p = type;}
};

struct InitSignal_EC: public IEvent, public EventBase {
	InitSignal_EC() :
			EventBase(InitSignal_EE) {
	}
virtual void setPortType (int type) { p = type;}
};

#endif //__EVENT_HPP_

