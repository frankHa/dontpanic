#ifndef DP_DBUS_TIMERANGE_H
#define DP_DBUS_TIMERANGE_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/timerange.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::TimeRange )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::TimeRange & range );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::TimeRange const& range );
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
