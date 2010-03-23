#ifndef DP_DBUS_UUID_H
#define DP_DBUS_UUID_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <QDBusArgument>

Q_DECLARE_METATYPE ( dp::Uuid )
// ---------------------------------------------------------------------------------
DP_EXPORT QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Uuid & uuid );
// ---------------------------------------------------------------------------------
DP_EXPORT QDBusArgument & operator << ( QDBusArgument &arg, dp::Uuid const& uuid );
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_UUID_H
