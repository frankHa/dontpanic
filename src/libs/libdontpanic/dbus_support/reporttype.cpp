#include <libdontpanic/dbus_support/reporttype.h>
#include <libdontpanic/dbus_support/reportdatafilter.h>
#include <libdontpanic/dbus_support/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportType & report_type )
  {
    Uuid _id;
    QString _name;
    bool _a;
    bool _p;
    ReportDataFilter &_af = report_type.activityFilter();
    ReportDataFilter &_pf = report_type.projectFilter();
    arg.beginStructure();
    arg >> _id >> _name >> _a >> _p >> _af >> _pf;
    arg.endStructure();
    report_type._M_id = _id;
    report_type.setTitle ( _name );
    report_type.setGroupByActivity(_a);
    report_type.setGroupByProject(_p);
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportType const& rt )
  {
    arg.beginStructure();
    arg << rt.id() << rt.title()<<rt.groupByActivity()<<rt.groupByProject()<<rt.activityFilter()<<rt.projectFilter();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
