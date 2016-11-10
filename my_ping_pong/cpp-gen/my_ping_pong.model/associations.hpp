#ifndef __ASSOCIATIONS_HPP__
#define __ASSOCIATIONS_HPP__

#include "runtime/association.hpp"
struct Player;
struct Table;
struct TableComposite: public Association<Table, Player> {
	struct table {
		typedef Table EdgeType;
	};
	struct player {
		typedef Player EdgeType;
	};
};

#endif //__ASSOCIATIONS_HPP_

