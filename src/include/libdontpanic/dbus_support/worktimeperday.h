#ifndef DP_DBUS_WORKTIMEPERDAY_H
#define DP_DBUS_WORKTIMEPERDAY_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/worktimeperday.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::WorktimePerDay )
Q_DECLARE_METATYPE ( dp::WorktimePerDayList )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::WorktimePerDay & wtpd );
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::WorktimePerDay const& wtpd );
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_WORKTIMEPERDAY_H
