#ifndef DP_DBUS_REPORT_DATA_H
#define DP_DBUS_REPORT_DATA_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/reportdata.h>
#include <QDBusArgument>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportData & filter );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, ReportData const& filter );
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
