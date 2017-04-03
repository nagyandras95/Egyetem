#include <iostream>
#include "deployment.hpp"
#include "init_maps.hpp"
#include "Table.hpp"
#include "event.hpp"

int main()
{
  Runtime* rt =
  deployment::initRuntime(); // the runtime type depends on deployment header options(default - threaded)
  StateMachine::initTransitionTables();
  rt->startRT();

  Table table;
  table.StarterPort->recive(std::shared_ptr<StartPlaying_EC>(new StartPlaying_EC()));
  std::cout << "The files are successfully compiled!\nYou can now modify the main.cpp" << std::endl;
  std::cin.get();
  return 0;
}
