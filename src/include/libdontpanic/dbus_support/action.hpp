#ifndef DP_DBUS_ACTION_HPP
#define DP_DBUS_ACTION_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/action.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Action & at );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, dp::Action const& at );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_ACTION_TEMPLATE_HPP
