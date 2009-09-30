#include "libdontpanic/dbus.hpp"
#include "applicationadaptor.h"
#include "timetrackeradaptor.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  // implementions for the well known Adaptor types:
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<Application> ( Application *obj )
  {
    return new ApplicationAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<dp::TimeTracker> ( dp::TimeTracker *obj )
  {
    return new TimeTrackerAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
