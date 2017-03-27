#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"
#include <iostream>
class PingPongInf
{
public:
	void send (std::shared_ptr<PingSignal_EC> s) {specialSend(s);}
	void send(std::shared_ptr<PongSignal_EC> s) { specialSend(s); std::cout << "pongsignal sended" << std::endl; }
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
