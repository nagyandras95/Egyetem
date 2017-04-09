#ifndef __ASSOCIATIONS_HPP__
#define __ASSOCIATIONS_HPP__

#include "runtime/association.hpp"
struct Player;
struct Table;
struct PingPongMatch;
struct Judge;
struct TableComposite: public Association<Table, Player> {
	struct table {
		typedef Table EdgeType;
	};
	struct player {
		typedef Player EdgeType;
	};
};
struct MatchJudgeComposite: public Association<PingPongMatch, Judge> {
	struct match {
		typedef PingPongMatch EdgeType;
	};
	struct judge {
		typedef Judge EdgeType;
	};
};
struct MatchTableComposite: public Association<PingPongMatch, Table> {
	struct match {
		typedef PingPongMatch EdgeType;
	};
	struct table {
		typedef Table EdgeType;
	};
};

#endif //__ASSOCIATIONS_HPP_

