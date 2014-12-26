//dp includes
#include "core/application.hpp"
#include "libdontpanic/dbus.hpp"
//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  dp::dbus().register_service("org.dontpanic").at_session_bus();
  dp::dbus().register_dp_custom_types();
  Application app(argc, argv);
  int result =  app.exec();
  qDebug()<<"bye...";
  return result;
}
// ---------------------------------------------------------------------------------
