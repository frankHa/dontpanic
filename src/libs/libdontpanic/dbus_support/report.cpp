#include <libdontpanic/dbus_support/report.h>
#include <libdontpanic/dbus_support/timerange.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Report & report )
{
  QString _t;
  dp::TimeRange _r;
  QString _d;
  arg.beginStructure();
  arg >> _t >> _r >> _d;
  arg.endStructure();
  report.setReportType(_t).setRange(_r).setReportData(_d);
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Report const& report )
{
  arg.beginStructure();
  arg << report.reportType()<<report.range()<<report.reportData();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
