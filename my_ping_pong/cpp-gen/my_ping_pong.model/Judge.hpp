#ifndef __JUDGE_HPP__
#define __JUDGE_HPP__

#include "statemachinebase.hpp"

#include "runtime/istatemachine.hpp"
#include "port.hpp"
#include "interfaces.hpp"
struct Judge: public StateMachineBase, public IStateMachine {
	static void initTransitionTable();
	bool process_event(EventBaseCRef);
	void setInitialState();
//RuntimeFunctions
	virtual void processEventVirtual();
	virtual void processInitTranstion();

	Judge();
	void initJudge();
	~Judge();

	template<typename T, typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename T, typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}
	enum States {
		Init_ST, Working_ST
	};

	enum Ports {
		StarterPort_PE = 2
	};

	BehvaiorPort<StartInf,EmptyInf> * StarterPort;

protected:
	typedef std::function<void(Judge&, EventBaseCRef)> ActionFuncType;
	typedef std::function<bool(Judge&, EventBaseCRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Judge::GuardAction> _mM;

private:
	void initStateMachine();

	void setState(int s_);
	void entry();
	void exit();

	int _cS;

	void Initialize(EventBaseCRef);

};

#include "associations.hpp"

#endif //__JUDGE_HPP_

