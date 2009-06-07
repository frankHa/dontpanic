//dp includes
#include "libdontpanic/dbus_support/Project.hpp"
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Project & project )
{
  uint64_t _id;
  QString _name;
  bool _visible;
  QDateTime _creation_date;
  arg.beginStructure();
  arg >> _id >> _name >> _visible >> _creation_date;
  arg.endStructure();
  project.setId ( _id );
  project.setName ( _name );
  project.setCreationDate ( _creation_date );
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Project const& project )
{
  arg.beginStructure();
  arg<<project.id()<<project.isVisible()<<project<<project.creationDate();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
