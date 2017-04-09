#include "deployment.hpp"
namespace deployment {
UsedRuntimePtr initRuntime() {
	ESContainer::FixedArray < ES::SharedPtr
			< Execution::Configuration >> conf(2);
	conf[0] = ES::SharedPtr < Execution::Configuration
			> (new Execution::Configuration(
					ES::SharedPtr < Execution::StateMachineThreadPool
							> (new Execution::StateMachineThreadPool()),
					ES::SharedPtr < Execution::LinearFunction
							> (new Execution::LinearFunction(1, 0.0)), 1));
	conf[1] = ES::SharedPtr < Execution::Configuration
			> (new Execution::Configuration(
					ES::SharedPtr < Execution::StateMachineThreadPool
							> (new Execution::StateMachineThreadPool()),
					ES::SharedPtr < Execution::LinearFunction
							> (new Execution::LinearFunction(1, 0.0)), 1));
	UsedRuntimePtr rt = UsedRuntimeType::getRuntimeInstance();
	rt->configure(conf);

	return rt;
}
}

