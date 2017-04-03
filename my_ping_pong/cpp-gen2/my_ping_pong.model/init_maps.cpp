#include "init_maps.hpp"
#include "Player.hpp"
#include "Judge.hpp"
namespace StateMachine {
void initTransitionTables() {
	Judge::initTransitionTable();
	Player::initTransitionTable();

	return;
}
}

