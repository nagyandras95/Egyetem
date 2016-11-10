#include "deployment.hpp"
namespace deployment {
Runtime* initRuntime() {
	ThreadConfiguration* conf = new ThreadConfiguration(1);
	conf->insertConfiguration(0,
			new Configuration(new StateMachineThreadPool(),
					new LinearFunction(1, 0.0), 1));
	Runtime* rt = Runtime::createRuntime();
	rt->configure(conf);

	return rt;
}
}

