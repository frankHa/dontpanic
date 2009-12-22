#ifndef DP_DBUS_QUUID_H
#define DP_DBUS_QUUID_H
#include <libdontpanic/defines.hpp>
#include <QUuid>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( QUuid )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, QUuid & uuid );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, QUuid const& uuid );
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_QUUID_H
