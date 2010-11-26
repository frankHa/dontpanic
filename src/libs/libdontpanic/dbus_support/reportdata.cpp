#include <libdontpanic/dbus_support/reportdata.h>
#include <libdontpanic/dbus_support/qdatetime.h>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::ReportData::Row )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportData & data )
  {
    QStringList &_h = data.headers();
    ReportData::Data &_d = data.data();
    ReportData::TypeList &_t = data.columnTypes();
    arg.beginStructure();
    arg >> _h >> _t >> _d;
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportData const& data )
  {
    arg.beginStructure();
    arg << data.headers() << data.columnTypes() << data.data();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
