#ifndef DP_DBUS_COMMON_H
#define DP_DBUS_COMMON_H
#include <defines.hpp>
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
namespace rp
{
  // ---------------------------------------------------------------------------------
  template<typename T>
  QDBusArgument const& operator >> ( QDBusArgument const&arg, boost::shared_ptr<T>  obj )
  {
    if ( obj.get() == 0 )
    {
      obj.reset ( new T() );
    }
    arg >> ( *obj );
    return arg;
  }
  // ---------------------------------------------------------------------------------
  template<typename T>
  QDBusArgument & operator << ( QDBusArgument &arg, boost::shared_ptr<T> const obj )
  {
    if ( obj.get() == 0 )
      return arg;
    arg << ( *obj );
    return arg;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //RP_DBUS_COMMON_H
