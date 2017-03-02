#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "runtime/ievent.hpp"
enum Events {
	InitSignal_EE, PingSignal_EE, PongSignal_EE, StartPlaying_EE
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

