#include "connectiontypes.hpp"
#include "istatemachine.hpp"
#include "ievent.hpp"
#include <iostream>
#ifndef PORT_HPP
#define PORT_HPP


template <typename RequiredInf, typename ProvidedInf>
class IPort;

template <typename RequiredInf, typename ProvidedInf>
class Port;

template <typename RequiredInf, typename ProvidedInf>
class PortImpl;

template <typename RequiredInf, typename ProvidedInf>
struct DelegationConnection;

template <typename RequiredInf, typename ProvidedInf>
struct AssemblyConnection;


struct IConnection;



template <typename RequiredInf, typename ProvidedInf>
class IPort : public RequiredInf::RequiredInfType , public ProvidedInf::ProvidedInfType
{
public:
	template <typename RequiredInf, typename ProvidedInf>
	friend class PortImpl;

	template <typename RequiredInf, typename ProvidedInf>
	friend struct AssemblyConnection;

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
	void setInnerConnection(IPort<RequiredInf, ProvidedInf> * innerPort) { connectionToInnerPort = innerPort; }
protected:
	
	IPort<RequiredInf, ProvidedInf> * connectionToInnerPort;


};

template <typename RequiredInf, typename ProvidedInf>
class BehaviorPort : public IPort<RequiredInf, ProvidedInf>
{
public:
	BehaviorPort(int type_, IStateMachine * owner_) : type(type_), owner(owner_) {}
	virtual ~BehaviorPort() {}
	int getType() const { return type; }
protected:

	int type;
	IStateMachine * owner;
};

struct IConnection
{
	virtual void fowardSendedMessageToConnectedPort(EventPtr signal) = 0;

};

template <typename RequiredInf, typename ProvidedInf>
struct AssemblyConnection : public IConnection
{
	AssemblyConnection (IPort<RequiredInf, ProvidedInf> * port_) : port(port_) {}
	virtual void fowardSendedMessageToConnectedPort (EventPtr signal)
	{
		port->reciveAny(signal);
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
		port->sendAny(signal);
	}
	
private:
	Port<RequiredInf , ProvidedInf> * port;
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
class BehavionPortImpl : public BehaviorPort <RequiredInf, ProvidedInf>
{
    public:
		BehavionPortImpl (int type_, IStateMachine * parent_) : BehaviorPort <RequiredInf, ProvidedInf> (type_,parent_) {}
		virtual ~BehavionPortImpl() {}
    protected:
        virtual void sendAny (EventPtr signal)
        {
			BehaviorPort <RequiredInf, ProvidedInf>::connectedPort->fowardSendedMessageToConnectedPort(signal);
        }

        virtual void reciveAny (EventPtr signal)
        {
			EventBase* realEvent = static_cast<EventBase*>(signal.get());
			realEvent->p = BehaviorPort <RequiredInf, ProvidedInf>::type;
			BehaviorPort <RequiredInf, ProvidedInf>::owner->send(signal);
        }


};

template <typename RequiredInf, typename ProvidedInf>
class PortImpl : public Port <RequiredInf, ProvidedInf>
{
public:
	PortImpl() : Port <RequiredInf, ProvidedInf>() {}
	virtual ~PortImpl() {}


protected:
	virtual void sendAny(EventPtr signal)
	{
		Port <RequiredInf, ProvidedInf>::connectedPort->fowardSendedMessageToConnectedPort(signal);
	}

	virtual void reciveAny(EventPtr signal)
	{
		if (Port <RequiredInf, ProvidedInf>::connectionToInnerPort != nullptr)
		{
			Port <RequiredInf, ProvidedInf>::connectionToInnerPort->reciveAny(signal);
		}
	}

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
