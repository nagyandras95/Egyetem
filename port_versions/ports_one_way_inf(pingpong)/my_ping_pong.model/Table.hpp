#ifndef __TABLE_HPP__
#define __TABLE_HPP__

struct Player;
#include "runtime/association.hpp"
#include "runtime/port.hpp"
#include "interfaces.hpp"

struct Table {
	Table();
	void initTable();
	~Table();

	Port<EmptyInf,StartInf> * StarterPort;

	AssociationEnd<Player> TableComposite_player = AssociationEnd < Player
			> (2, 2);
	template<typename T, typename EndPointName>
	void link(typename EndPointName::EdgeType*) {
	}
	template<typename T, typename EndPointName>
	void unlink(typename EndPointName::EdgeType*) {
	}

private:

};

#include "associations.hpp"
template<>
void Table::link<TableComposite, typename TableComposite::player>(Player*);
template<>
void Table::unlink<TableComposite, typename TableComposite::player>(Player*);

#endif //__TABLE_HPP_

