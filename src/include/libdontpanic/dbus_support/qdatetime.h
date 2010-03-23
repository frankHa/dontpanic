#ifndef DP_DBUS_QDATETIME_H
#define DP_DBUS_QDATETIME_H
#include <libdontpanic/defines.hpp>
#include <QDateTime>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( QDateTime )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, QDateTime & time );
  // ---------------------------------------------------------------------------------
  DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, QDateTime const& time );
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
