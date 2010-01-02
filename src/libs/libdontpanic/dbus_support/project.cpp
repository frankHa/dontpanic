//dp includes
#include "libdontpanic/dbus_support/project.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
// ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Project & project )
  {
    QString _id;
    QString _name;
    QDateTime _creation_date;
    arg.beginStructure();
    arg >> _id >> _name >> _creation_date;
    arg.endStructure();
    project._M_id =  _id;
    project.setName ( _name );
    project.setCreationDate ( _creation_date );
    return arg;
  }
// ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Project const& project )
  {
    arg.beginStructure();
    arg << project.id().toString() << project.name() << project.creationDate();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}
