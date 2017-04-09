#ifndef __DEPLOYMENT_HPP__
#define __DEPLOYMENT_HPP__

#include "runtime/runtime.hpp"
#include "runtime/ESRoot/Types.hpp"

using UsedRuntimePtr = ES::RuntimePtr<Execution::ConfiguredThreadedRT>;
using UsedRuntimeType = Execution::IRuntime<Execution::ConfiguredThreadedRT>;

namespace deployment {
UsedRuntimePtr initRuntime();
}

#endif //__DEPLOYMENT_HPP_

