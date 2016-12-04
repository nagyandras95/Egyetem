#include "connectiontable.hpp"
#include "istatemachine.hpp"
#include <iostream>
#ifndef PORT_HPP
#define PORT_HPP

struct IConnection 
{		
	virtual void fowardSendedMessageToConnectedPort (EventPtr signal) = 0;

};

template <typename RequiredInf, typename ProvidedInf>
class IPort : public RequiredInf
{
public:
	void setAssemblyConnectedPort (IPort<ProvidedInf,RequiredInf> * connectedPort_) {
		connectedPort = new AssemblyConnection<ProvidedInf,RequiredInf>(connectedPort_);
	}
	void setDelgationConnectedPort (IPort<RequiredInf,ProvidedInf> * connectedPort_) {
		connectedPort = new DelegationConnection<ProvidedInf,RequiredInf>(connectedPort_);
	}

protected:
	IConnection * connectedPort;
};

template <typename RequiredInf, typename ProvidedInf>
class Port : public IPort<RequiredInf, ProvidedInf>
{
public:
	virtual ~Port() {}
	void fowardSignal(EventPtr s) { sepcialSend(s); }
	void setInnerConnection(IPort<RequiredInf, ProvidedInf> * innerPort) { connectionToInnerPort = innerPort; }
protected:
	
	IPort<RequiredInf, ProvidedInf> * connectionToInnerPort;


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
class MultiThreadedPort : public BehvaiorPort <RequiredInf, ProvidedInf>
{
    public:
		MultiThreadedPort (int type_, IStateMachine * parent_) : BehvaiorPort <RequiredInf, ProvidedInf> (type_,parent_),
		_stop(false), 
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

/*template <typename RequiredInf, typename ProvidedInf>
class Port : public IPort
{
    public:
        Port (int type_, StateMachineI * parent_) : type (type_), parent(parent_)
        {
            portId = ConnectionTable::REG_AND_GET_NEXT_ID(this);
        }

        void send (std::shared_ptr<RequiredInf> signal) {specialSend(signal);}
        void recive (std::shared_ptr<ProvidedInf> signal) {specialRecive(signal);}
	int getId() const {return portId;}
	int getType () const {return type;}
    protected:

        int type;
        StateMachineI * parent;
        int portId;

        virtual void specialSend (std::shared_ptr<RequiredInf> signal) = 0;
        virtual void specialRecive (std::shared_ptr<ProvidedInf> signal) = 0;


};

template <typename RequiredInf, typename ProvidedInf>
class MultiThreadedPort : public Port <RequiredInf,ProvidedInf>
{
    public:
        MultiThreadedPort (int type_, StateMachineI * parent_) : Port<RequiredInf,ProvidedInf> (type_,parent_),
	_stop(false), 
        sender (&MultiThreadedPort::senderTask, this),
        recevier (&MultiThreadedPort::receiverTask, this) {}



    protected:
        virtual void specialSend (std::shared_ptr<RequiredInf> signal)
        {
           signalsToSend.push_back (signal);
        }

        virtual void specialRecive (std::shared_ptr<ProvidedInf> signal)
        {
            signalsToRecive.push_back (signal);
        }

        void senderTask ()
        {
            while (!_stop) {
                std::shared_ptr<RequiredInf> signal;
                signalsToSend.pop_front(signal);
                //if (signal.get() != nullptr)
                //{
                    IPort * p = ConnectionTable::GET_CONNECTED_PORT (Port<RequiredInf,ProvidedInf>::portId);
		    Port<ProvidedInf,RequiredInf> * sp = static_cast<Port<ProvidedInf,RequiredInf> *>(p);
                    sp->recive(signal);
                //}

            }
        }

        void receiverTask ()
        {
            while (!_stop)
            {
                std::shared_ptr<ProvidedInf> signal;
                signalsToRecive.pop_front(signal);
                //if (signal.get() != nullptr)
                //{
                    signal->setPortType(Port<RequiredInf,ProvidedInf>::type);
                    Port<RequiredInf,ProvidedInf>::parent->send (signal);

                //}


            }
        }

		std::atomic_bool _stop;
		ThreadSafeQueue<std::shared_ptr<RequiredInf> > signalsToSend;
		ThreadSafeQueue<std::shared_ptr<ProvidedInf> > signalsToRecive;
		std::thread sender;
		std::thread recevier;

};*/

#endif // PORT_HPP
