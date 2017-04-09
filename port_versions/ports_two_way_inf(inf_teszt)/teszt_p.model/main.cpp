#include <iostream>

#include "Env.hpp"
#include "deployment.hpp"
#include "A.hpp"
#include "B.hpp"
#include "runtime/port.hpp"
int main()
{
  Env::initEnvironment();
  UsedRuntimePtr rt = UsedRuntimeType::getRuntimeInstance();
  //rt->startRT(); // the runtime can be started later

  Model::A a;
  Model::B b;

  connect<Inf1, Inf2>(a.A_Port, b.B_Port);


  std::cout << "The files are successfully compiled!\nYou can now modify the main.cpp" << std::endl;
  std::cin.get();
  return 0;
}
