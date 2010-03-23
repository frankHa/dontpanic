#include <libdontpanic/dbus_support/qdatetime.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, QDateTime & time )
  {
    QString _id;
    arg.beginStructure();
    arg >> _id;
    arg.endStructure();
    time = QDateTime::fromString ( _id );
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, QDateTime const& time )
  {
    arg.beginStructure();
    arg << time.toString();
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
