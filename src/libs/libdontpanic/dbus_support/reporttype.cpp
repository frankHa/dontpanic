#include <libdontpanic/dbus_support/reporttype.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportType & report_type )
  {
    QString _id;
    QString _name;
    arg.beginStructure();
    arg >> _id >> _name;
    arg.endStructure();
    report_type._M_id = _id;
    report_type.setTitle ( _name );
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportType const& report_type )
  {
    arg.beginStructure();
    arg << report_type.id().toString() << report_type.title();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
