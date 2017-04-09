#ifndef __EVENT_HPP__
#define __EVENT_HPP__

namespace Model {
#include "runtime/ievent.hpp"
enum Events {
	InitSignal_EE, Sign1_EE, Sign2_EE, Sign3_EE, Sign4_EE
};
struct Sign1_EC: public EventBase {
	Sign1_EC() :
			EventBase(Sign1_EE) {
	}
};

struct Sign2_EC: public EventBase {
	Sign2_EC() :
			EventBase(Sign2_EE) {
	}
};

struct Sign3_EC: public EventBase {
	Sign3_EC() :
			EventBase(Sign3_EE) {
	}
};

struct Sign4_EC: public EventBase {
	Sign4_EC() :
			EventBase(Sign4_EE) {
	}
};

struct InitSignal_EC: public EventBase {
	InitSignal_EC() :
			EventBase(InitSignal_EE) {
	}
};

}

#endif //__EVENT_HPP_

