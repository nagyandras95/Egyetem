#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"
#include <iostream>

class EmptyInf {
protected:
	template <typename RequiredInf, typename ProvidedInf>
	friend struct DelegationConnection;

	virtual void sendAny(EventPtr s) = 0;
};

class PingPongInf
{
public:
	void send (std::shared_ptr<PingSignal_EC> s) { sendAny(s); }
	void send (std::shared_ptr<PongSignal_EC> s) { sendAny(s); }

protected:
	virtual void sendAny (EventPtr s) = 0;
};


class StartInf
{
public:
	void send (std::shared_ptr<StartPlaying_EC> s) {sendAny(s);}
protected:
	virtual void sendAny (EventPtr s) = 0;
};



#endif
