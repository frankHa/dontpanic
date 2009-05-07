//dp includes
#include "Application.hpp"
#include "libdontpanic/dbus.hpp"
//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  dp::dbus().register_service("org.dontpanic").at_session_bus();
  Application app(argc, argv);
  int result =  app.exec();
  qDebug()<<"bye...";
  return result;
}
// ---------------------------------------------------------------------------------
