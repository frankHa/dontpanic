#ifndef DP_DBUS_PROJECT_HPP
#define DP_DBUS_PROJECT_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/project.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Project & project );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, dp::Project const& project );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_PROJECT_HPP
