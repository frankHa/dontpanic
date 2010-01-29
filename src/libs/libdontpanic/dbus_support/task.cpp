//dp includes
#include "libdontpanic/dbus_support/task.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Task & task )
  {
    QString _name;
    QString uuid;
    bool _solo;
    bool _chargeable;
    QDateTime _creation_date;
    arg.beginStructure();
    arg >> uuid >> _name >> _solo >> _chargeable >> _creation_date;
    arg.endStructure();
    task._M_id = uuid;
    task.setName ( _name )
    .setIsSoloEffort ( _solo )
    .setIsChargeable ( _chargeable )
    .setCreationDate ( _creation_date );
    return arg;
  }
// ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Task const& task )
  {
    arg.beginStructure();
    arg << task.id().toString() << task.name()
    << task.isSoloEffort()
    << task.isChargeable() << task.creationDate();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}
