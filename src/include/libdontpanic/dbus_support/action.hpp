#ifndef DP_DBUS_ACTION_HPP
#define DP_DBUS_ACTION_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/action.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Action )
Q_DECLARE_METATYPE ( dp::ActionList )
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Action & at );
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Action const& at );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_ACTION_TEMPLATE_HPP
