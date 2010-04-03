#include "application.hpp"
#include "application.moc"

#include "libdontpanic/dbus.hpp"
#include "context.h"
#include "persistencebackend.hpp"
#include "actiontemplatemanager.h"
#include "projectmanager.h"
#include "reportmanager.h"
#include "taskmanager.h"
#include "timetracker.h"
#include "plannedworkingtimemanager.h"


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
    void init_context();
    // ---------------------------------------------------------------------------------
    bool init_storage_backend();
    // ---------------------------------------------------------------------------------
    void init_action_template_manager();
    // ---------------------------------------------------------------------------------
    void init_projectmanager();
    // ---------------------------------------------------------------------------------
    void init_reportmanager();
    // ---------------------------------------------------------------------------------
    void init_taskmanager();
    // ---------------------------------------------------------------------------------
    void init_timetracker();
    // ---------------------------------------------------------------------------------
    void init_planned_workingtime_manager();
    // ---------------------------------------------------------------------------------
    void register_with_session_bus();
    // ---------------------------------------------------------------------------------
  private:
    // ---------------------------------------------------------------------------------
    Application * _M_self;
    // ---------------------------------------------------------------------------------
};
// ---------------------------------------------------------------------------------
// implementation Application:
// ---------------------------------------------------------------------------------
Application::Application ( int &argc, char** argv )
    : QCoreApplication ( argc, argv )
    , d ( new ApplicationPrivate ( this ) ) {}
// ---------------------------------------------------------------------------------
Application::~Application()
{
  delete d;
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
  init_context();
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_context()
{
  dp::context();
}

// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::register_with_session_bus()
{
  //qDebug() << "registering at the session bus now...";
  //dp::dbus().register_object ( _M_self ).at_session_bus().as ( "/Application" );
}

// ---------------------------------------------------------------------------------
