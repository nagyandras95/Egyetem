#ifndef __TOP_HPP__
#define __TOP_HPP__

#include "runtime/ESRoot/Types.hpp"
#include "runtime/association.hpp"
namespace Model {
struct A;
struct B;

}

namespace Model {
struct Top {
	Top();
	void initTop();
	~Top();

	AssociationEnd<A> TopAComposite_a = AssociationEnd < A > (1, 1);
	AssociationEnd<B> TopBComposite_b = AssociationEnd < B > (1, 1);
	template<typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}

private:

};

}
#include "associations.hpp"
namespace Model {
template<>
void Top::link<typename TopAComposite::a>(A*);
template<>
void Top::unlink<typename TopAComposite::a>(A*);
template<>
void Top::link<typename TopBComposite::b>(B*);
template<>
void Top::unlink<typename TopBComposite::b>(B*);

}

#endif //__TOP_HPP_

