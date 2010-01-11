#include "libdontpanic/dbus.hpp"
#include "timetrackeradaptor.h"
#include "projectmanageradaptor.h"
#include "taskmanageradaptor.h"
#include "actiontemplatemanageradaptor.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  // implementions for the well known Adaptor types:
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<dp::TimeTracker> ( dp::TimeTracker *obj )
  {
    return new TimeTrackerAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<dp::ProjectManager> ( dp::ProjectManager *obj )
  {
    return new ProjectManagerAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<dp::TaskManager> ( dp::TaskManager *obj )
  {
    return new TaskManagerAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<dp::ActionTemplateManager> ( dp::ActionTemplateManager *obj )
  {
    return new ActionTemplateManagerAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
