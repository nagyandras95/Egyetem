#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"

class PingPongInf
{
public:
	void send (std::shared_ptr<PingSignal_EC> s) {specialSend(s);}
	void send (std::shared_ptr<PongSignal_EC> s) {specialSend(s);}
protected:
	virtual void specialSend (EventPtr s) = 0;
};

class StartInf
{
public:
	void send (std::shared_ptr<StartPlaying_EC> s) {specialSend(s);}
protected:
	virtual void specialSend (EventPtr s) = 0;
};


#endif
