#include <iostream>
#include "deployment.hpp"
#include "init_maps.hpp"
#include "Table.hpp"
//#include "Class1.hpp"
//#include "Class2.hpp"

int main()
{
  Runtime* rt =
  deployment::initRuntime(); // the runtime type depends on deployment header options(default - threaded)
  StateMachine::initTransitionTables();
  rt->startRT();

  Table table;
  std::cout << "The files are successfully compiled!\nYou can now modify the main.cpp" << std::endl;
  std::cin.get();
  return 0;
}
