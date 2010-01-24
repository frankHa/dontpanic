//dp includes
#include "libdontpanic/dbus_support/actiontemplate.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::ActionTemplate & at )
  {
    QString uuid;
    QString task;
    QString project;
    QString ct;
    QString name;
    QString comment;
    QString icon;
    arg.beginStructure();
    arg >> uuid >> task >> project >> ct >> name >> comment>>icon;
    arg.endStructure();
    at._M_id = uuid;
    at.setTask ( task );
    at.setProject( project );
    at.setCollaborationType( ct );
    at.setName(name);
    at.setComment(comment);
    at.setIcon(icon);
    return arg;
  }
// ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::ActionTemplate const& at )
  {
    arg.beginStructure();
    arg << at.id().toString() << at.task().toString()
    << at.project().toString()
    << at.collaborationType().toString() << at.name()<<at.comment()<<at.icon();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}
