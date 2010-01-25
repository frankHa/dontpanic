#ifndef DP_DBUS_QDATETIME_H
#define DP_DBUS_QDATETIME_H
#include <libdontpanic/defines.hpp>
#include <QDateTime>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( QDateTime )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, QDateTime & time );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, QDateTime const& uuid );
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
