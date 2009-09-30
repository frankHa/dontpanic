#include "application.hpp"
#include "application.moc"

#include "libdontpanic/dbus.hpp"
#include "persistencebackend.hpp"
#include "timetracker.h"

//Qt includes
#include <QDebug>
#include <QDBusConnection>
// ---------------------------------------------------------------------------------
// declaration of ApplicationPrivate:
// ---------------------------------------------------------------------------------
class Application::ApplicationPrivate
{
    // ---------------------------------------------------------------------------------
  public:
    // ---------------------------------------------------------------------------------
    ApplicationPrivate ( Application* self );
    // ---------------------------------------------------------------------------------
  public:
    // ---------------------------------------------------------------------------------
    QString hello();
    // ---------------------------------------------------------------------------------
    void exit();
    // ---------------------------------------------------------------------------------
  private:
    // ---------------------------------------------------------------------------------
    void init();
    // ---------------------------------------------------------------------------------
    bool init_storage_backend();
    // ---------------------------------------------------------------------------------
    void init_timetracker();
    // ---------------------------------------------------------------------------------
    void register_with_session_bus();
    // ---------------------------------------------------------------------------------
  private:
    // ---------------------------------------------------------------------------------
    Application * _M_self;
    // ---------------------------------------------------------------------------------
    dp::PersistenceBackend * _M_persistence;
    dp::TimeTracker *_M_timetracker;
    // ---------------------------------------------------------------------------------
};
// ---------------------------------------------------------------------------------
// implementation Application:
// ---------------------------------------------------------------------------------
Application::Application ( int &argc, char** argv )
    : QCoreApplication ( argc, argv )
    , d ( new ApplicationPrivate ( this ) ) {}
// ---------------------------------------------------------------------------------
QString Application::hello()
{
  return d->hello();
}
// ---------------------------------------------------------------------------------
void Application::exit()
{
  d->exit();
}
// ---------------------------------------------------------------------------------
// implementation ApplicationPrivate:
// ---------------------------------------------------------------------------------
Application::ApplicationPrivate::ApplicationPrivate ( Application *self )
    : _M_self ( self )
{
  init();
}
// ---------------------------------------------------------------------------------
QString Application::ApplicationPrivate::hello()
{
  return "dontpanic says 'hello'";
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::exit()
{
  qDebug() << "exiting now!";
  QCoreApplication::exit ( 0 );
}
// ---------------------------------------------------------------------------------
//private stuff:
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init()
{
  register_with_session_bus();
  init_storage_backend();
  init_timetracker();
}
// ---------------------------------------------------------------------------------
bool Application::ApplicationPrivate::init_storage_backend()
{
  return dp::persistence().init();
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_timetracker()
{
  _M_timetracker = new dp::TimeTracker(_M_self);
  dp::dbus().register_object(_M_timetracker).at_session_bus().as("/TimeTracker");
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::register_with_session_bus()
{
  //qDebug() << "registering at the session bus now...";
  //dp::dbus().register_object ( _M_self ).at_session_bus().as ( "/Application" );
}

// ---------------------------------------------------------------------------------
