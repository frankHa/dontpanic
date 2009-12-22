#include <libdontpanic/dbus_support//quuid.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, QUuid & uuid )
{
  QString _id;
  arg.beginStructure();
  arg >> _id;
  arg.endStructure();
  uuid = _id;
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, QUuid const& uuid )
{
  arg.beginStructure();
  arg << uuid.toString();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
