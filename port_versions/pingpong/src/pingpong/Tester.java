package pingpong;

import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.execution.ModelExecutor;
import pingpong.model.PingPongMatch;


public class Tester {
	static PingPongMatch match;
	static void init() {
		match = new PingPongMatch ();
		Action.start(match);
	}

	public static void main(String[] args) {
		ModelExecutor.create().setTraceLogging(false).run(Tester::init);
	}

}
