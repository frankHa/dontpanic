//dp includes
#include "libdontpanic/dbus_support/task.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Task & task )
  {
    QString _name;
    QString uuid;
    bool _visible;
    bool _solo;
    bool _chargeable;
    QDateTime _creation_date;
    arg.beginStructure();
    arg >> uuid >> _name >> _visible >> _solo >> _chargeable >> _creation_date;
    arg.endStructure();
    task._M_id = uuid;
    task.set_name ( _name );
    task.set_is_visible ( _visible );
    task.set_is_solo_effort ( _solo );
    task.set_is_chargeable ( _chargeable );
    task.set_creation_date ( _creation_date );
    return arg;
  }
// ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Task const& task )
  {
    arg.beginStructure();
    arg << task.id().toString() << task.name()
    << task.is_visible() << task.is_solo_effort()
    << task.is_chargeable() << task.creation_date();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}
