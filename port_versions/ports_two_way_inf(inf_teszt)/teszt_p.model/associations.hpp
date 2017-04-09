#ifndef __ASSOCIATIONS_HPP__
#define __ASSOCIATIONS_HPP__

#include "runtime/association.hpp"
namespace Model {
struct A;
struct B;
struct Top;
struct TopAComposite {
	struct top {
		typedef Top EdgeType;
	};
	struct a {
		typedef A EdgeType;
	};
};
struct TopBComposite {
	struct top {
		typedef Top EdgeType;
	};
	struct b {
		typedef B EdgeType;
	};
};

}

#endif //__ASSOCIATIONS_HPP_

