#include "PersistanceBackendDBusWrapper.hpp"
#include "PersistanceBackend.hpp"
#include "libdontpanic/Project.hpp"
#include "libdontpanic/DBus.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PersistanceBackendDBusWrapper::PersistanceBackendDBusWrapper ( QObject* parent ) : QObject ( parent )
  {
    dbus().register_object ( this ).at_session_bus().as ( "org.dontpanic.Persistance" );
  }

  // ---------------------------------------------------------------------------------
  bool PersistanceBackendDBusWrapper::persist ( Project & p )
  {
    return persistance().persist ( p ).was_successful();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
