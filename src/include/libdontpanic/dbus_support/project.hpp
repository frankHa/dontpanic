#ifndef DP_DBUS_PROJECT_HPP
#define DP_DBUS_PROJECT_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/project.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Project )
Q_DECLARE_METATYPE ( dp::ProjectList )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument DP_EXPORT const& operator >> ( QDBusArgument const&arg, dp::Project & project );
  // ---------------------------------------------------------------------------------
  QDBusArgument DP_EXPORT  & operator << ( QDBusArgument &arg, dp::Project const& project );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_PROJECT_HPP
