//dp includes
#include "libdontpanic/dbus_support/action.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Action& at )
  {
    QString uuid;
    QString task;
    QString project;
    QString ct;
    QString name;
    QString comment;
    QDateTime start;
    QDateTime end;
    bool reviewed;
    bool billed;
    arg.beginStructure();
    arg >> uuid >> task >> project >> ct >> name >> comment>>start>>end>>reviewed>>billed;
    arg.endStructure();
    at._M_id = uuid;
    at.setTask ( task )
    .setProject( project )
    .setCollaborationType( ct )
    .setName(name)
    .setComment(comment)
    .setStartTime(start)
    .setEndTime(end)
    .setReviewed(reviewed)
    .setBilled(billed);
    
    return arg;
  }
// ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::Action const& at )
  {
    arg.beginStructure();
    arg << at.id().toString() << at.task().toString()
    << at.project().toString()
    << at.collaborationType().toString() 
    << at.name()<<at.comment()
    <<at.startTime()<<at.endTime()
    <<at.reviewed()<<at.billed();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}
