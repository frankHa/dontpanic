#ifndef DP_DBUS_WORKTIMEPERDAY_H
#define DP_DBUS_WORKTIMEPERDAY_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/worktimeperday.h>
#include <QDBusArgument>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::WorktimePerDay & wtpd );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, dp::WorktimePerDay const& wtpd );
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_WORKTIMEPERDAY_H
