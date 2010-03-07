#include "application.hpp"
#include "application.moc"

#include "libdontpanic/dbus.hpp"
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
    dp::PersistenceBackend * _M_persistence;
    dp::TimeTracker *_M_timetracker;
    dp::ProjectManager *_M_projectmanager;
    dp::ReportManager *_M_reportmanager;
    dp::TaskManager *_M_taskmanager;
    dp::ActionTemplateManager *_M_action_template_manager;
    dp::PlannedWorkingTimeManager *_M_planned_workingtime_manager;
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
  init_storage_backend();
  init_action_template_manager();
  init_projectmanager();
  init_reportmanager();
  init_taskmanager();
  init_timetracker();  
  init_planned_workingtime_manager();
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
void Application::ApplicationPrivate::init_action_template_manager()
{
  _M_action_template_manager = new dp::ActionTemplateManager ( _M_self );
  dp::dbus().register_object ( _M_action_template_manager ).at_session_bus().as ( "/ActionTemplateManager" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_reportmanager()
{
  _M_reportmanager = new dp::ReportManager ( _M_self );
  dp::dbus().register_object ( _M_reportmanager ).at_session_bus().as ( "/ReportManager" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_timetracker()
{
  _M_timetracker = new dp::TimeTracker ( _M_self );
  dp::dbus().register_object ( _M_timetracker ).at_session_bus().as ( "/TimeTracker" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::init_planned_workingtime_manager()
{
  _M_planned_workingtime_manager = new dp::PlannedWorkingTimeManager ( _M_self );
  dp::dbus().register_object ( _M_planned_workingtime_manager ).at_session_bus().as ( "/PlannedWorkingTimeManager" );
}
// ---------------------------------------------------------------------------------
void Application::ApplicationPrivate::register_with_session_bus()
{
  //qDebug() << "registering at the session bus now...";
  //dp::dbus().register_object ( _M_self ).at_session_bus().as ( "/Application" );
}

// ---------------------------------------------------------------------------------
