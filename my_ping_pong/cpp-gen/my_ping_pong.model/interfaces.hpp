#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include "runtime/runtimetypes.hpp"
#include <iostream>


class EmptyReqInf {

	template <typename RequiredInf, typename ProvidedInf>
	friend struct DelegationConnection;

protected:
	virtual void sendAny(EventPtr s) = 0;
};

class EmptyProvInf {
protected:
	virtual void reciveAny(EventPtr s) = 0;
};

class EmptyInf {
public:


	using RequiredInfType = EmptyReqInf;
	using ProvidedInfType = EmptyProvInf;
};

class PingPongReqInf
{
public:
	void send (std::shared_ptr<PingSignal_EC> s){ sendAny(s); }
	void send(std::shared_ptr<PongSignal_EC> s) { sendAny(s); }

protected:
	virtual void sendAny (EventPtr s) = 0;
};

class PingPongProvInf {
public:
	void recive(std::shared_ptr<PingSignal_EC> s) { reciveAny(s); }
	void recive(std::shared_ptr<PongSignal_EC> s) { reciveAny(s); }

protected:
	virtual void reciveAny(EventPtr s) = 0;
};

class PingPongInf
{
public:
	using RequiredInfType = PingPongReqInf;
	using ProvidedInfType = PingPongProvInf;
};

class StartReqInf
{
public:
	void send (std::shared_ptr<StartPlaying_EC> s) {sendAny(s);}
protected:
	virtual void sendAny (EventPtr s) = 0;
};


class StartProvInf {
public:
	void recive(std::shared_ptr<StartPlaying_EC> s) { reciveAny(s); }
protected:
	virtual void reciveAny(EventPtr s) = 0;
};


class StartInf
{
public:
	using RequiredInfType = StartReqInf;
	using ProvidedInfType = StartProvInf;
};
#endif
