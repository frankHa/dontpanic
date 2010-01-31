#ifndef DP_DBUS_REPORT_H
#define DP_DBUS_REPORT_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::Report )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Report & report );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Report const& report );
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
