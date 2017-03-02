#include "connectiontypes.hpp"
#include "istatemachine.hpp"
#include "ievent.hpp"
#include <iostream>
#ifndef PORT_HPP
#define PORT_HPP

class EmptyInf {
protected:
	virtual void specialSend (EventPtr) {};
};

class MessageReciver
{
public:
	void recive (EventPtr signal) {specialRecive(signal);}

protected:
	virtual void specialRecive (EventPtr signal) = 0;
};
struct IConnection 
{		
	virtual void fowardSendedMessageToConnectedPort (EventPtr signal) = 0;

};


template <typename RequiredInf, typename ProvidedInf>
class Port;

template <typename RequiredInf, typename ProvidedInf>
class IPort : public RequiredInf, public MessageReciver
{
public:
	void setAssemblyConnectedPort (IPort<ProvidedInf,RequiredInf> * connectedPort_);
	void setDelgationConnectedPort (Port<RequiredInf,ProvidedInf> * connectedPort_);

protected:
	IConnection * connectedPort;
};

template <typename RequiredInf, typename ProvidedInf>
class Port : public IPort<RequiredInf, ProvidedInf>
{
public:
	Port () : connectionToInnerPort(nullptr) {}
	virtual ~Port() {}
	void fowardSignal(EventPtr s) { IPort<RequiredInf, ProvidedInf>::specialSend(s); }
	void setInnerConnection(IPort<RequiredInf, ProvidedInf> * innerPort) { connectionToInnerPort = innerPort; }
protected:
	
	IPort<RequiredInf, ProvidedInf> * connectionToInnerPort;


};

template <typename RequiredInf, typename ProvidedInf>
struct AssemblyConnection : public IConnection
{
	AssemblyConnection (IPort<RequiredInf, ProvidedInf> * port_) : port(port_) {}
	virtual void fowardSendedMessageToConnectedPort (EventPtr signal)
	{
		port->recive(signal);
	}
	
private:
	IPort<RequiredInf,ProvidedInf> * port;
};

template <typename RequiredInf, typename ProvidedInf>
struct DelegationConnection : public IConnection
{
	DelegationConnection (Port<RequiredInf, ProvidedInf> * port_) : port(port_) {}

	virtual void fowardSendedMessageToConnectedPort (EventPtr signal)
	{
		port->fowardSignal(signal);
	}
	
private:
	Port<RequiredInf , ProvidedInf> * port;
};

template <typename RequiredInf, typename ProvidedInf>
class BehvaiorPort : public IPort<RequiredInf, ProvidedInf>
{
public:
	BehvaiorPort(int type_, IStateMachine * owner_) : type(type_), owner(owner_) {}
	virtual ~BehvaiorPort() {}
	int getType() const { return type; }
protected:

	int type;
	IStateMachine * owner;
};

template<typename Inf1, typename Inf2>
void connect(IPort<Inf1, Inf2> * p1, IPort <Inf2, Inf1> * p2)
{
	p1->setAssemblyConnectedPort(p2);
	p2->setAssemblyConnectedPort(p1);
}

template<typename Inf1, typename Inf2>
void connect(IPort<Inf1, Inf2> * p1, Port <Inf1, Inf2> * p2)
{
	p1->setDelgationConnectedPort(p2);
	p2->setInnerConnection(p1);
}


template <typename RequiredInf, typename ProvidedInf>
class MultiThreadedBehaviorPort : public BehvaiorPort <RequiredInf, ProvidedInf>
{
    public:
		MultiThreadedBehaviorPort (int type_, IStateMachine * parent_) : BehvaiorPort <RequiredInf, ProvidedInf> (type_,parent_),
		_stop(false), 
        sender (&MultiThreadedBehaviorPort::senderTask, this),
        recevier (&MultiThreadedBehaviorPort::receiverTask, this)
		{
			signalsToSend.startQueue();
			signalsToRecive.startQueue();
		}
		
		~MultiThreadedBehaviorPort() {
			signalsToSend.stopQueue();
			signalsToRecive.stopQueue();
		}



    protected:
        virtual void specialSend (EventPtr signal)
        {
           signalsToSend.push_back (signal);
        }

        virtual void specialRecive (EventPtr signal)
        {
            signalsToRecive.push_back (signal);
        }

        void senderTask ()
        {
            while (!_stop) {
                EventPtr signal;
                signalsToSend.pop_front(signal);
				if (!_stop) {
					BehvaiorPort <RequiredInf, ProvidedInf>::connectedPort->fowardSendedMessageToConnectedPort(signal);
				}

            }
        }

        void receiverTask ()
        {
            while (!_stop)
            {
                EventPtr signal;
                signalsToRecive.pop_front(signal);
				if (!_stop)
				{
					EventBase* realEvent = static_cast<EventBase*>(signal.get());
					realEvent->p = BehvaiorPort <RequiredInf, ProvidedInf>::type;
					BehvaiorPort <RequiredInf,ProvidedInf>::owner->send (signal);
				}



            }
        }

		std::atomic_bool _stop;
		ThreadSafeQueue<EventPtr> signalsToSend;
		ThreadSafeQueue<EventPtr> signalsToRecive;
		std::thread sender;
		std::thread recevier;

};

template <typename RequiredInf, typename ProvidedInf>
class MultiThreadedPort : public Port <RequiredInf, ProvidedInf>
{
    public:
		MultiThreadedPort () : _stop(false), 
        sender (&MultiThreadedPort::senderTask, this),
        recevier (&MultiThreadedPort::receiverTask, this)
		{
			signalsToSend.startQueue();
			signalsToRecive.startQueue();
		}
		
		~MultiThreadedPort() {
			signalsToSend.stopQueue();
			signalsToRecive.stopQueue();
		}



    protected:
        virtual void specialSend (EventPtr signal)
        {
           signalsToSend.push_back (signal);
        }

        virtual void specialRecive (EventPtr signal)
        {
            signalsToRecive.push_back (signal);
        }

        void senderTask ()
        {
            while (!_stop) {
                EventPtr signal;
                signalsToSend.pop_front(signal);
				if (!_stop) {
					Port <RequiredInf, ProvidedInf>::connectedPort->fowardSendedMessageToConnectedPort(signal);
				}

            }
        }

        void receiverTask ()
        {
            while (!_stop)
            {
            	EventPtr signal;
            	signalsToRecive.pop_front(signal);
		if (!_stop && Port <RequiredInf, ProvidedInf>::connectionToInnerPort != nullptr)
		{
			Port <RequiredInf, ProvidedInf>::connectionToInnerPort->recive (signal);
		}



            }
        }

		std::atomic_bool _stop;
		ThreadSafeQueue<EventPtr> signalsToSend;
		ThreadSafeQueue<EventPtr> signalsToRecive;
		std::thread sender;
		std::thread recevier;

};

template <typename RequiredInf, typename ProvidedInf>
void IPort<RequiredInf,ProvidedInf>::setAssemblyConnectedPort (IPort<ProvidedInf,RequiredInf> * connectedPort_) {
	connectedPort = new AssemblyConnection<ProvidedInf,RequiredInf>(connectedPort_);
}

template <typename RequiredInf, typename ProvidedInf>
void IPort<RequiredInf,ProvidedInf>::setDelgationConnectedPort (Port<RequiredInf,ProvidedInf> * connectedPort_) {
		connectedPort = new DelegationConnection<RequiredInf,ProvidedInf>(connectedPort_);
}

#endif // PORT_HPP
