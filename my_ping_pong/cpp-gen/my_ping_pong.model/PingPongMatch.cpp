#include "PingPongMatch.hpp"
#include "Table.hpp"
#include "Judge.hpp"
#include "event.hpp"
#include "associations.hpp"
#include "runtime/standard_functions.hpp"
#include "runtime/itimer.hpp"
#include "runtime/timer.hpp"

PingPongMatch::PingPongMatch() {
	initPingPongMatch();
}
void PingPongMatch::initPingPongMatch() {
	Judge* judge_us0;
	Table* table_us1;
	Judge* gen0;
	Judge* temp0 = nullptr;
	gen0 = temp0;
	gen0 = new Judge();
	judge_us0 = gen0;
	Table* gen1;
	Table* temp1 = nullptr;
	gen1 = temp1;
	gen1 = new Table();
	table_us1 = gen1;
	action::link<MatchTableComposite, typename MatchTableComposite::match,
			typename MatchTableComposite::table>(this, table_us1);
	action::link<MatchJudgeComposite, typename MatchJudgeComposite::match,
			typename MatchJudgeComposite::judge>(this, judge_us0);

	connect (table_us1->StarterPort,judge_us0->StarterPort);

	judge_us0->startSM();

}
PingPongMatch::~PingPongMatch() {
}

