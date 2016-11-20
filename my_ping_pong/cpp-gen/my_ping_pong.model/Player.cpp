#include "Player.hpp"
#include <string>
#include "deployment.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "event.hpp"
#include "runtime/standard_functions.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"
#include <iostream>

std::unordered_multimap<EventState, Player::GuardAction> Player::_mM;
void Player::initTransitionTable() {
	Player::_mM.emplace(EventState(Events::InitSignal_EE, Init_ST, NoPort_PE),
			GuardAction(GuardFuncType(&Player::defaultGuard),
					ActionFuncType(&Player::Initialize)));
	Player::_mM.emplace(
			EventState(Events::PingSignal_EE, Playing_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::guard1),
					ActionFuncType(&Player::DenyPPing)));
	Player::_mM.emplace(
			EventState(Events::PongSignal_EE, Playing_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::guard2),
					ActionFuncType(&Player::RecivePPong)));
	Player::_mM.emplace(
			EventState(Events::PongSignal_EE, Playing_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::guard1),
					ActionFuncType(&Player::DenyPPong)));
	Player::_mM.emplace(
			EventState(Events::PongSignal_EE, Waiting_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::defaultGuard),
					ActionFuncType(&Player::ReciveWPong)));
	Player::_mM.emplace(
			EventState(Events::StartPlaying_EE, Waiting_ST, NoPort_PE),
			GuardAction(GuardFuncType(&Player::defaultGuard),
					ActionFuncType(&Player::Starting)));
	Player::_mM.emplace(
			EventState(Events::PingSignal_EE, Playing_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::guard2),
					ActionFuncType(&Player::RecivePPing)));
	Player::_mM.emplace(
			EventState(Events::PingSignal_EE, Waiting_ST, PingPongPort_PE),
			GuardAction(GuardFuncType(&Player::defaultGuard),
					ActionFuncType(&Player::ReciveWPing)));
}

void Player::initStateMachine() {
	setPoolId(0);
	Runtime::createRuntime()->setupObject(this);
	setInitialState();
	PingPongPort = new MultiThreadedPort<PingPongInf,PingPongInf>(PingPongPort_PE,this);
}

bool Player::process_event(EventBaseCRef e_) {
	bool handled = false;
	//std::cout << e_.t << " " << e_.p << " " << _cS << std::endl;
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
void Player::processEventVirtual() {
	IEvent* base = getNextMessage().get();
	EventBase* realEvent = dynamic_cast<EventBase*>(base);
	process_event(*realEvent);
	deleteNextMessage();
}

void Player::processInitTranstion() {
	InitSignal_EC init;
	process_event(init);
}

void Player::setState(int s_) {
	_cS = s_;
	entry();
}

void Player::setInitialState() {
	setState (Init_ST);
}
bool Player::guard2(EventBaseCRef) {
	bool gen0;
	bool temp0 = (this->hitCount <= this->maxHit);
	gen0 = temp0;
	return gen0;
}
bool Player::guard1(EventBaseCRef) {
	bool gen0;
	bool temp0 = (this->hitCount > this->maxHit);
	gen0 = temp0;
	return gen0;
}
bool Player::guard0(EventBaseCRef) {
	bool gen0;
	bool temp0 = (this->hitCount <= this->maxHit);
	gen0 = temp0;
	return gen0;
}
bool Player::guard3(EventBaseCRef) {
	bool gen0;
	bool temp0 = (this->hitCount > this->maxHit);
	gen0 = temp0;
	return gen0;
}
void Player::Initialize(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::Initialize" << std::endl;
#endif
	setState (Waiting_ST);

}

void Player::Starting(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::Starting" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player start playing");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PingSignal_EC>(new PingSignal_EC()));
	setState (Playing_ST);
	

}

void Player::RecivePPing(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::RecivePPing" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived ping");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PongSignal_EC>(new PongSignal_EC()));
	int temp3 = (this->hitCount + 1);
	this->hitCount = temp3;
	setState (Playing_ST);

}

void Player::DenyPPing(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::DenyPPing" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived ping");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PongSignal_EC>(new PongSignal_EC()));
	int temp3 = (this->hitCount + 1);
	this->hitCount = temp3;
	setState (Finishing_ST);

}

void Player::RecivePPong(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::RecivePPong" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived pong");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PingSignal_EC>(new PingSignal_EC()));
	int temp3 = (this->hitCount + 1);
	this->hitCount = temp3;
	setState (Playing_ST);

}

void Player::DenyPPong(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::DenyPPong" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived pong");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PingSignal_EC>(new PingSignal_EC()));
	int temp3 = (this->hitCount + 1);
	this->hitCount = temp3;
	setState (Finishing_ST);

}

void Player::ReciveWPing(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::ReciveWPing" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived ping");
	std::string temp2 = (temp0 + temp1);
	PingPongPort->send(std::shared_ptr<PongSignal_EC>(new PongSignal_EC()));
	action::log(temp2);
	setState (Playing_ST);

}

void Player::ReciveWPong(EventBaseCRef) {
#ifndef NDEBUG
	std::cout << "Player::ReciveWPong" << std::endl;
#endif
	std::string temp0 = conversion::to_string(this->name);
	std::string temp1 = conversion::to_string(" player recived pong");
	std::string temp2 = (temp0 + temp1);
	action::log(temp2);
	PingPongPort->send(std::shared_ptr<PingSignal_EC>(new PingSignal_EC()));
	setState (Playing_ST);

}

void Player::entry() {
}

void Player::exit() {
}

Player::Player(std::string name_, int maxHit_) {
	initPlayer(name_, maxHit_);
}
void Player::initPlayer(std::string name_, int maxHit_) {
	std::string name_us0;
	name_us0 = name_;
	this->name = name_us0;
	this->maxHit = 10;
	this->hitCount = 0;

	initStateMachine();
}
Player::~Player() {
	Runtime::createRuntime()->removeObject(this);
}


