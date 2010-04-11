#include <libdontpanic/dbus_support/reportdatafilter.h>
#include <libdontpanic/dbus_support/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportDataFilter & filter )
  {
    int _t;
    UuidList &_e=filter.selection();
    arg.beginStructure();
    arg>>_t>>_e;
    arg.endStructure();
    filter.setFilterType(_t);
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportDataFilter const& filter )
  {
    arg.beginStructure();
    arg<<filter.filterType()<<filter.selection();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
