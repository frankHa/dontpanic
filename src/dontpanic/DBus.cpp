#include "libdontpanic/DBus.hpp"
#include "applicationadaptor.h"
#include "persistenceadaptor.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  // implementions for the well known Adaptor types:
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<Application> ( Application *obj )
  {
    return new ApplicationAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
  template<>
  QDBusAbstractAdaptor* create_dbus_adaptor_for<PersistenceBackendDBusWrapper> ( PersistenceBackendDBusWrapper *obj )
  {
    return new PersistanceAdaptor ( obj );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
