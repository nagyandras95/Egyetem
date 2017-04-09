#ifndef __PINGPONGMATCH_HPP__
#define __PINGPONGMATCH_HPP__

struct Table;
struct Judge;
#include "runtime/association.hpp"

struct PingPongMatch {
	PingPongMatch();
	void initPingPongMatch();
	~PingPongMatch();

	AssociationEnd<Judge> MatchJudgeComposite_judge = AssociationEnd < Judge
			> (1, 1);
	AssociationEnd<Table> MatchTableComposite_table = AssociationEnd < Table
			> (1, 1);
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
void PingPongMatch::link<MatchJudgeComposite,
		typename MatchJudgeComposite::judge>(Judge*);
template<>
void PingPongMatch::unlink<MatchJudgeComposite,
		typename MatchJudgeComposite::judge>(Judge*);
template<>
void PingPongMatch::link<MatchTableComposite,
		typename MatchTableComposite::table>(Table*);
template<>
void PingPongMatch::unlink<MatchTableComposite,
		typename MatchTableComposite::table>(Table*);

#endif //__PINGPONGMATCH_HPP_

