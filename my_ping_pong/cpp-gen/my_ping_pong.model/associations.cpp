#include "associations.hpp"
#include "Player.hpp"
#include "Table.hpp"
template<>
void Table::link<TableComposite, typename TableComposite::player>(
		Player* object) {
	TableComposite_player.addAssoc(object);
}
template<>
void Table::unlink<TableComposite, typename TableComposite::player>(
		Player* object) {
	TableComposite_player.removeAssoc(object);
}

