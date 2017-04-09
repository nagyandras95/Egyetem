#include "Top.hpp"
#include "A.hpp"
#include "B.hpp"
#include "event.hpp"
#include "associations.hpp"
#include "runtime/Action.hpp"
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"

namespace Model {
Top::Top() {
	initTop();
}
void Top::initTop() {
	A* a_us0;
	B* b_us1;
	A* gen0;
	A* temp0 = nullptr;
	gen0 = temp0;
	gen0 = new A();
	a_us0 = gen0;
	B* gen1;
	B* temp1 = nullptr;
	gen1 = temp1;
	gen1 = new B();
	b_us1 = gen1;
	Action::link<typename TopAComposite::a, typename TopAComposite::top>(a_us0,
			this);
	Action::link<typename TopBComposite::b, typename TopBComposite::top>(b_us1,
			this);

}
Top::~Top() {
}

}

