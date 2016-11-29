#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"

class MessageReciver
{
public:
	void recive (EventPtr signal) {specialRecive(signal);}

protected:
	virtual void specialRecive (EventPtr signal) = 0;
};

class PingPongInf : public MessageReciver
{
public:
	void send (std::shared_ptr<PingSignal_EC> s) {specialSend(s);}
	void send (std::shared_ptr<PongSignal_EC> s) {specialSend(s);}
protected:
	virtual void specialSend (EventPtr s) = 0;
};


#endif
