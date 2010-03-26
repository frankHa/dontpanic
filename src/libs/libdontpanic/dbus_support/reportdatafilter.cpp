#include <libdontpanic/dbus_support/reportdatafilter.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportDataFilter & filter )
  {
    arg.beginStructure();
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportDataFilter const& filter )
  {
    arg.beginStructure();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
