#ifndef DP_DBUS_TIMERANGE_H
#define DP_DBUS_TIMERANGE_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/timerange.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::TimeRange )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::TimeRange & range );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, dp::TimeRange const& range );
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
