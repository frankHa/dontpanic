#include "Application.hpp"
#include "Application.moc"

#include "libdontpanic/dbus.hpp"

//Qt includes
#include <QDebug>
#include <QDBusConnection>
// ---------------------------------------------------------------------------------
Application::Application ( int &argc, char** argv )
    : QCoreApplication ( argc, argv )
{
  register_with_session_bus();
}
// ---------------------------------------------------------------------------------
QString Application::hello()
{
  return "dontpanic says 'hello'";
}
// ---------------------------------------------------------------------------------
void Application::exit()
{
  qDebug() << "exiting now!";
  QCoreApplication::exit ( 0 );
}
// ---------------------------------------------------------------------------------
void Application::register_with_session_bus()
{
  qDebug() << "registering at the session bus now...";
  dp::dbus().register_object(this).at_session_bus().as("/Application");
}

// ---------------------------------------------------------------------------------
