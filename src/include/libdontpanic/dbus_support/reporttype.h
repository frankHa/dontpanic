#ifndef DP_DBUS_REPORTTYPE_H
#define DP_DBUS_REPORTTYPE_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/reporttype.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::ReportType )
Q_DECLARE_METATYPE ( dp::ReportTypeList )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportType & report_type );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, ReportType const& report_type );
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
