#ifndef DP_DBUS_TASK_HPP
#define DP_DBUS_TASK_HPP
//dp includes
#include "defines.hpp"
#include "libdontpanic/Task.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Task )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Task & project );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Task const& project );
// ---------------------------------------------------------------------------------
#endif //DP_DBUS_TASK_HPP
