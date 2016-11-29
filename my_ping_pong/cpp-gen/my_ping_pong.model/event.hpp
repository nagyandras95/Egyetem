#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "runtime/ievent.hpp"
#include "interfaces.hpp"

enum Events {
	InitSignal_EE = 13, PingSignal_EE = 17, PongSignal_EE = 19, StartPlaying_EE = 23
};
struct PingSignal_EC: public EventBase {
	PingSignal_EC() :
			EventBase(PingSignal_EE) {
	}
};

struct PongSignal_EC: public EventBase {
	PongSignal_EC() :
			EventBase(PongSignal_EE) {
	}
};

struct StartPlaying_EC: public EventBase {
	StartPlaying_EC() :
			EventBase(StartPlaying_EE) {
	}
};

struct InitSignal_EC: public EventBase {
	InitSignal_EC() :
			EventBase(InitSignal_EE) {
	}
};

#endif //__EVENT_HPP_

