#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "statemachinebase.hpp"

#include "runtime/istatemachine.hpp"

#include <string>
#include "runtime/port.hpp"
#include "interfaces.hpp"

struct Player: public StateMachineBase, public IStateMachine {
	static void initTransitionTable();
	bool process_event(EventBaseCRef);
	void setInitialState();
//RuntimeFunctions
	virtual void processEventVirtual();
	virtual void processInitTranstion();

	int hitCount;
	int maxHit;
	std::string name;
	Player(std::string, int);
	void initPlayer(std::string, int);
	~Player();

	template<typename T, typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename T, typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}
	enum States {
		Init_ST = 2, Waiting_ST = 2, Playing_ST = 3, Finishing_ST = 4
	};

	enum Ports {
		PingPongPort_PE = 2, StarterPort_PE = 3
	};

	BehaviorPort<PingPongInf, PingPongInf> * PingPongPort;
	BehaviorPort<EmptyInf, StartInf> * StarterPort;
protected:
	typedef std::function<void(Player&, EventBaseCRef)> ActionFuncType;
	typedef std::function<bool(Player&, EventBaseCRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Player::GuardAction> _mM;

private:
	void initStateMachine();

	void setState(int s_);
	void entry();
	void exit();

	int _cS;
	bool guard0(EventBaseCRef);
	bool guard1(EventBaseCRef);
	bool guard2(EventBaseCRef);
	bool guard3(EventBaseCRef);

	void Initialize(EventBaseCRef);
	void Starting(EventBaseCRef);
	void RecivePPing(EventBaseCRef);
	void DenyPPing(EventBaseCRef);
	void RecivePPong(EventBaseCRef);
	void DenyPPong(EventBaseCRef);
	void ReciveWPing(EventBaseCRef);
	void ReciveWPong(EventBaseCRef);

};

#include "associations.hpp"

#endif //__PLAYER_HPP_

