#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"


class PingPongRequiredInf
{
public:
	void send (std::shared_ptr<PingSignal_EC> s) {specialSend(s);}
	void send (std::shared_ptr<PongSignal_EC> s) {specialSend(s);}
protected:
	virtual void specialSend (EventPtr s) = 0;
};

class PingPongProvidedInf
{
public:

	void convertAndRecive (EventPtr s)
	{
		switch(s->getType())
		{
			
			case PingSignal_EE :
				recive (std::static_pointer_cast<PingSignal_EC>(s));
			break;
			
			case PongSignal_EE:
				recive (std::static_pointer_cast<PongSignal_EC>(s));
			break;
			default : /*hiba*/ break;
				
		}
	}
	void recive (std::shared_ptr<PingSignal_EC> s) {specialRecive(s);}
	void recive (std::shared_ptr<PongSignal_EC> s) {specialRecive(s);}
protected:
	virtual void specialRecive (EventPtr s) = 0;
};


#endif
