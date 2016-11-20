#include "connectiontable.hpp"
#include "statemachineI.hpp"
#include <iostream>
#ifndef PORT_HPP
#define PORT_HPP

template <typename RequiredInf, typename ProvidedInf>
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

};

#endif // PORT_HPP
