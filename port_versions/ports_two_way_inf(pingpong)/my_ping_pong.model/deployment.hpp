#ifndef __DEPLOYMENT_HPP__
#define __DEPLOYMENT_HPP__

#include "threadconfiguration.hpp"
#include "runtime/runtime.hpp"

using Runtime = RuntimeI<ConfiguratedThreadedRT>;

namespace deployment {
Runtime* initRuntime();
}

#endif //__DEPLOYMENT_HPP_

