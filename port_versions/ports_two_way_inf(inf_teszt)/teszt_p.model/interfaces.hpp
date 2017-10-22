#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include "event.hpp"
#include <iostream>
template <typename SendInf, typename ReciveInf>
class IntegratedInf
{
public:
	using RequiredInfType = SendInf;
	using ProvidedInfType = ReciveInf;
};

class EmptyReqInf {

	template <typename RequiredInf, typename ProvidedInf>
	friend struct DelegationConnection;

protected:
	virtual void sendAny(ES::EventRef s) = 0;
};

class EmptyProvInf {
protected:
	virtual void reciveAny(ES::EventRef s) = 0;
};

using EmptyInf = IntegratedInf<EmptyReqInf, EmptyProvInf>;


class Inf1ReqInf
{
public:
	void send(ES::SharedPtr<Model::Sign1_EC> s) { sendAny(s); }
	void send(ES::SharedPtr<Model::Sign2_EC> s) { sendAny(s); }

protected:
	virtual void sendAny (ES::EventRef s) = 0;
};

class Inf1ProvInf {
public:
	void recive(ES::SharedPtr<Model::Sign1_EC > s) { reciveAny(s); }
	void recive(ES::SharedPtr<Model::Sign2_EC > s) { reciveAny(s); }

protected:
	virtual void reciveAny(ES::EventRef s) = 0;
};

#define INTEGRATED_DEF(InfName, InfReq, InfProv) using InfName = IntegratedInf<InfReq, InfProv>



//using Inf1 = IntegratedInf<Inf1ReqInf, Inf1ProvInf>;
INTEGRATED_DEF(Inf1, Inf1ReqInf, Inf1ProvInf);

class Inf2ReqInf
{
public:
	void send(ES::SharedPtr<Model::Sign3_EC> s) { sendAny(s); }
	void send(ES::SharedPtr<Model::Sign4_EC> s) { sendAny(s); }
protected:
	virtual void sendAny (ES::EventRef s) = 0;
};


class Inf2ProvInf {
public:
	void recive(ES::SharedPtr<Model::Sign3_EC > s) { reciveAny(s); }
	void recive(ES::SharedPtr<Model::Sign4_EC > s) { reciveAny(s); }
protected:
	virtual void reciveAny(ES::EventRef s) = 0;
};

INTEGRATED_DEF(Inf2, Inf2ReqInf, Inf2ProvInf);
#endif
