#include "PersistenceBackendDBusWrapper.hpp"
#include "PersistenceBackend.hpp"
#include "libdontpanic/Project.hpp"
#include "libdontpanic/DBus.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PersistenceBackendDBusWrapper::PersistenceBackendDBusWrapper ( QObject* parent ) : QObject ( parent )
  {
    dbus().register_object ( this ).at_session_bus().as ( "org.dontpanic.Persistance" );
  }

  // ---------------------------------------------------------------------------------
  bool PersistenceBackendDBusWrapper::persist ( Project & p )
  {
    return persistance().persist ( p ).was_successful();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
