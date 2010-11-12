#include <libdontpanic/dbus_support/reportdata.h>
#include <libdontpanic/dbus_support/qdatetime.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportData & data )
  {
    QStringList &_h= data.headers();
    ReportData::Data &_d = data.data();
    ReportData::TypeList &_t = data.columnTypes();
    arg.beginStructure();
    arg>>_h>>_d >> _t;
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportData const& data )
  {
    arg.beginStructure();
    arg<< data.headers()<< data.data()<<data.columnTypes();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
