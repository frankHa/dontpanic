#include <libdontpanic/dbus_support/report.h>
#include <libdontpanic/dbus_support/timerange.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Report & report )
{
  bool _v;
  QString _t;
  dp::TimeRange _r;
  QString _d;
  arg.beginStructure();
  arg >> _v >> _t >> _r >> _d;
  arg.endStructure();
  report.setValid(_v).setReportType(_t).setRange(_r).setReportData(_d);
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Report const& report )
{
  arg.beginStructure();
  arg << report.isValid() << report.reportType() << report.range() << report.reportData();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
