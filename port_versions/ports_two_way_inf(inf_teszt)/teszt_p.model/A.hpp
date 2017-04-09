#ifndef __A_HPP__
#define __A_HPP__

#include "runtime/ESRoot/Types.hpp"
#include "runtime/port.hpp"
#include "interfaces.hpp"
namespace Model {

}

namespace Model {
struct A {
	A();
	void initA();
	~A();

	template<typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}

	Port<Inf1, Inf2> * A_Port;

private:

};

}
#include "associations.hpp"
namespace Model {

}

#endif //__A_HPP_

