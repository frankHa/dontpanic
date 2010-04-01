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
    QString _icon;
    bool _a;
    bool _p;
    int _t;
    ReportDataFilter &_af = report_type.taskFilter();
    ReportDataFilter &_pf = report_type.projectFilter();
    arg.beginStructure();
    arg >> _id >> _name >> _icon >> _a >> _p >> _t >> _af >> _pf;
    arg.endStructure();
    report_type._M_id = _id;
    report_type.setName ( _name );
    report_type.setIcon(_icon);
    report_type.setGroupByTask(_a);
    report_type.setGroupByProject(_p);
    report_type.setGroupByTimeInterval(_t);
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportType const& rt )
  {
    arg.beginStructure();
    arg << rt.id() << rt.name()<<rt.icon()<<rt.groupByTask()<<rt.groupByProject()<<rt.groupByTimeInterval()<<rt.taskFilter()<<rt.projectFilter();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
