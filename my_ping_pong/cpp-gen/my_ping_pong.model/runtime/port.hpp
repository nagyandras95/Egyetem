#include "connectiontable.hpp"
#include "istatemachine.hpp"
#include <iostream>
#ifndef PORT_HPP
#define PORT_HPP

template <typename RequiredInf, typename ProvidedInf>
class Port : public IPort, public RequiredInf
{
public:
    Port (int type_, IStateMachine * parent_) : type (type_), parent(parent_) {}
	virtual ~Port() {}
	int getType () const {return type;}
	void setConnectedPort (ProvidedInf* connectedPort_) {connectedPort = connectedPort_;}
protected:

        int type;
        IStateMachine * parent;
		ProvidedInf* connectedPort;


};


template <typename RequiredInf, typename ProvidedInf>
class MultiThreadedPort : public Port <RequiredInf, ProvidedInf>
{
    public:
        MultiThreadedPort (int type_, IStateMachine * parent_) : Port <RequiredInf, ProvidedInf> (type_,parent_),
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
					Port <RequiredInf, ProvidedInf>::connectedPort->recive(signal);
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
					realEvent->p = Port <RequiredInf, ProvidedInf>::type;
					Port <RequiredInf,ProvidedInf>::parent->send (signal);
				}



            }
        }

		std::atomic_bool _stop;
		ThreadSafeQueue<EventPtr> signalsToSend;
		ThreadSafeQueue<EventPtr> signalsToRecive;
		std::thread sender;
		std::thread recevier;

};

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
