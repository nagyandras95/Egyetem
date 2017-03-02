#include "associations.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include "PingPongMatch.hpp"
#include "Judge.hpp"
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
template<>
void PingPongMatch::link<MatchJudgeComposite,
		typename MatchJudgeComposite::judge>(Judge* object) {
	MatchJudgeComposite_judge.addAssoc(object);
}
template<>
void PingPongMatch::unlink<MatchJudgeComposite,
		typename MatchJudgeComposite::judge>(Judge* object) {
	MatchJudgeComposite_judge.removeAssoc(object);
}
template<>
void PingPongMatch::link<MatchTableComposite,
		typename MatchTableComposite::table>(Table* object) {
	MatchTableComposite_table.addAssoc(object);
}
template<>
void PingPongMatch::unlink<MatchTableComposite,
		typename MatchTableComposite::table>(Table* object) {
	MatchTableComposite_table.removeAssoc(object);
}

