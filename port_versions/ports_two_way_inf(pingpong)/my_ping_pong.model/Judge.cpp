#include "Judge.hpp"
#include "deployment.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "event.hpp"
#include "runtime/standard_functions.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"

std::unordered_multimap<EventState, Judge::GuardAction> Judge::_mM;
void Judge::initTransitionTable() {
	Judge::_mM.emplace(EventState(Events::InitSignal_EE, Init_ST, NoPort_PE),
			GuardAction(GuardFuncType(&Judge::defaultGuard),
					ActionFuncType(&Judge::Initialize)));
}

void Judge::initStateMachine() {
	setPoolId(0);
	Runtime::createRuntime()->setupObject(this);
	setInitialState();
}

bool Judge::process_event(EventBaseCRef e_) {
	bool handled = false;
	auto range = _mM.equal_range(EventState(e_.t, _cS, e_.p));
	if (range.first != _mM.end()) {
		for (auto it = range.first; it != range.second; ++it) {
			if ((it->second).first(*this, e_)) //Guard call
					{
				exit();
				(it->second).second(*this, e_); //Action Call
				handled = true;
				break;
			}
		}
	}
	return handled;
}
void Judge::processEventVirtual() {
	IEvent* base = getNextMessage().get();
	EventBase* realEvent = static_cast<EventBase*>(base);
	process_event(*realEvent);
	deleteNextMessage();
}

void Judge::processInitTranstion() {
	InitSignal_EC init;
	process_event(init);
}

void Judge::setState(int s_) {
	_cS = s_;
	entry();
}

void Judge::setInitialState() {
	setState (Init_ST);
}
void Judge::Initialize(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Judge::Initialize" << std::endl;
#endif
	//StarterPort->send(std::shared_ptr<StartPlaying_EC>(new StartPlaying_EC()));
	setState (Working_ST);

}

void Judge::entry() {
}

void Judge::exit() {
}

Judge::Judge() {
	StarterPort = new BehavionPortImpl<StartInf,EmptyInf>(StarterPort_PE,this);
	initJudge();
}
void Judge::initJudge() {

	initStateMachine();
}
Judge::~Judge() {
	Runtime::createRuntime()->removeObject(this);
}


