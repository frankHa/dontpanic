#include "Application.hpp"
#include "Application.moc"

#include "applicationadaptor.h"

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
void Application::exit()
{
  qDebug() << "exiting now!";
  QCoreApplication::exit ( 0 );
}
// ---------------------------------------------------------------------------------
void Application::register_with_session_bus()
{
  qDebug() << "registering at the session bus now...";
  new ApplicationAdaptor ( this );
  QDBusConnection dbus = QDBusConnection::sessionBus();
  if(dbus.registerObject ( "/Application", this ))
  {
    qDebug()<<"yeah, success :)";
  } else
  {
    qDebug()<<"uh oh, something went wrong :(";
  }
}

// ---------------------------------------------------------------------------------
