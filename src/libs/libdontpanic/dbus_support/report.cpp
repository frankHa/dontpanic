#include <libdontpanic/dbus_support/report.h>
#include <libdontpanic/dbus_support/timerange.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::Report & report )
{
  dp::TimeRange _r;
  QString _d;
  arg.beginStructure();
  arg >> _r >> _d;
  arg.endStructure();
  report.setRange(_r).setReportData(_d);
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::Report const& report )
{
  arg.beginStructure();
  arg << report.range()<<report.reportData();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
