#ifndef DP_DBUS_TASK_HPP
#define DP_DBUS_TASK_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/task.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Task )
Q_DECLARE_METATYPE ( dp::TaskList )
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Task & project );
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Task const& project );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_TASK_HPP
