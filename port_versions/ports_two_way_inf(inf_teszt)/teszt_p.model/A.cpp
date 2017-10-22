#include "A.hpp"
#include "event.hpp"
#include "runtime/Action.hpp"
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"

namespace Model {
A::A() {
	initA();
}
void A::initA() {
	A_Port = new PortImpl<Inf1, Inf2>();
}
A::~A() {
}

}

