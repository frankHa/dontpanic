#include <libdontpanic/dbus_support/qdatetime.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, QDateTime & time )
  {
    uint _secs;
    arg.beginStructure();
    arg >> _secs;
    arg.endStructure();
    time.setTime_t( _secs );
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, QDateTime const& time )
  {
    arg.beginStructure();
    arg << time.toTime_t();
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
