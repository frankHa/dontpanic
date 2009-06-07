#ifndef DP_DBUS_PROJECT_HPP
#define DP_DBUS_PROJECT_HPP
//dp includes
#include "defines.hpp"
#include "libdontpanic/Project.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Project )
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Project & project );
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Project const& project );
// ---------------------------------------------------------------------------------
#endif //DP_DBUS_PROJECT_HPP
