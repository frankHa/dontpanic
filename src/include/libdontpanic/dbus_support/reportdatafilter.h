#ifndef DP_DBUS_REPORT_DATA_FILTER_H
#define DP_DBUS_REPORT_DATA_FILTER_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/reportdatafilter.h>
#include <QDBusArgument>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportDataFilter & filter );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, ReportDataFilter const& filter );
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
