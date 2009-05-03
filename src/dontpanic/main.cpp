//dp includes
#include "Application.hpp"
//std includes
#include <iostream>
// ---------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Application app(argc, argv);
  int result =  app.exec();
  std::cout<<"bye..."<<std::endl;
  return result;
}
// ---------------------------------------------------------------------------------
