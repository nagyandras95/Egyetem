#include "Table.hpp"
#include "Player.hpp"
#include "event.hpp"
#include "associations.hpp"
#include "runtime/standard_functions.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"
#include "runtime/connectiontable.hpp"
Table::Table() {
	initTable();
}
void Table::initTable() {
	Player* player1_us0;
	Player* player2_us1;
	Player* gen0;
	Player* temp0 = nullptr;
	gen0 = temp0;
	gen0 = new Player("Player1", 10);
	player1_us0 = gen0;
	Player* gen1;
	Player* temp1 = nullptr;
	gen1 = temp1;
	gen1 = new Player("Player2", 10);
	player2_us1 = gen1;
	action::link<TableComposite, typename TableComposite::table,
			typename TableComposite::player>(this, player1_us0);
	action::link<TableComposite, typename TableComposite::table,
			typename TableComposite::player>(this, player2_us1);

	player1_us0->PingPongPort->setConnectedPort(player2_us1->PingPongPort);
	player2_us1->PingPongPort->setConnectedPort(player1_us0->PingPongPort);


	player1_us0->startSM();
	player2_us1->startSM();
	
	player1_us0->send(EventPtr(new StartPlaying_EC()));

}
Table::~Table() {
}

