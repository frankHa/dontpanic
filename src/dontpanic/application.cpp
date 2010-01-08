#include "application.hpp"
#include "application.moc"

#include "libdontpanic/dbus.hpp"
#include "persistencebackend.hpp"
#include "projectmanager.h"
#include "taskmanager.h"
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
    void exit();
    // ---------------------------------------------------------------------------------
  private:
    // ---------------------------------------------------------------------------------
    void init();
    // ---------------------------------------------------------------------------------
    bool init_storage_backend();
    // ---------------------------------------------------------------------------------
    void init_projectmanager();
    // ---------------------------------------------------------------------------------
    void init_taskmanager();
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
    dp::ProjectManager *_M_projectmanager;
    dp::TaskManager *_M_taskmanager;
    // ---------------------------------------------------------------------------------
};
// ---------------------------------------------------------------------------------
// implementation Application:
// ---------------------------------------------------------------------------------
Application::Application ( int &argc, char** argv )
    : QCoreApplication ( argc, argv )
    , d ( new ApplicationPrivate ( this ) ) {}
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
  init_projectmanager();
  init_taskmanager();
  init_timetracker();
}
// ---------------------------------------------------------------------------------
bool Application::ApplicationPrivate::init_storage_backend()
{
  return dp::persistence().init();
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_projectmanager()
{
  _M_projectmanager = new dp::ProjectManager ( _M_self );
  dp::dbus().register_object ( _M_projectmanager ).at_session_bus().as ( "/ProjectManager" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_taskmanager()
{
  _M_taskmanager = new dp::TaskManager ( _M_self );
  dp::dbus().register_object ( _M_taskmanager ).at_session_bus().as ( "/TaskManager" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_timetracker()
{
  _M_timetracker = new dp::TimeTracker ( _M_self );
  dp::dbus().register_object ( _M_timetracker ).at_session_bus().as ( "/TimeTracker" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::register_with_session_bus()
{
  //qDebug() << "registering at the session bus now...";
  //dp::dbus().register_object ( _M_self ).at_session_bus().as ( "/Application" );
}

// ---------------------------------------------------------------------------------
