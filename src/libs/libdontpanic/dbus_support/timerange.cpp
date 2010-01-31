#include <libdontpanic/dbus_support/timerange.h>
// ---------------------------------------------------------------------------------
QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::TimeRange & range )
{
  QDateTime _f;
  QDateTime _t;
  arg.beginStructure();
  arg >> _f >> _t;
  arg.endStructure();
  range.setFrom(_f).setTo(_t);
  return arg;
}
// ---------------------------------------------------------------------------------
QDBusArgument & operator << ( QDBusArgument &arg, dp::TimeRange const& range )
{
  arg.beginStructure();
  arg << range.from()<<range.to();
  arg.endStructure();
  return arg;
}
// ---------------------------------------------------------------------------------
