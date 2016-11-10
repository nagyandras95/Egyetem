package my_ping_pong;

import hu.elte.txtuml.api.model.Action;
import hu.elte.txtuml.api.model.execution.ModelExecutor;
import my_ping_pong.model.Table;


public class Tester {

	static void init() {
		Table table = new Table ();
		Action.start(table);
	}

	public static void main(String[] args) {
		ModelExecutor.create().setTraceLogging(false).run(Tester::init);
	}

}
