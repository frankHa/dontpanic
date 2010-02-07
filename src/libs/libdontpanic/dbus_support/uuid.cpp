#include <libdontpanic/dbus_support/uuid.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Uuid & uuid )
{
  QString _id;
  arg.beginStructure();
  arg >> _id;
  arg.endStructure();
  uuid = _id;
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Uuid const& uuid )
{
  arg.beginStructure();
  arg << uuid.toString();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
