//dp includes
#include "Application.hpp"
//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Application app(argc, argv);
  int result =  app.exec();
  qDebug()<<"bye...";
  return result;
}
// ---------------------------------------------------------------------------------
