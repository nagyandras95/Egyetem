#ifndef __B_HPP__
#define __B_HPP__

#include "runtime/ESRoot/Types.hpp"
#include "runtime/port.hpp"
#include "interfaces.hpp"
namespace Model {

}

namespace Model {
struct B {
	B();
	void initB();
	~B();

	template<typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}

	Port<Inf2, Inf1> * B_Port;
private:

};

}
#include "associations.hpp"
namespace Model {

}

#endif //__B_HPP_

