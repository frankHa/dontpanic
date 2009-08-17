#include "PersistenceBackendDBusWrapper.hpp"
#include "PersistenceBackend.hpp"
#include "libdontpanic/Project.hpp"
#include "libdontpanic/DBus.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PersistenceBackendDBusWrapper::PersistenceBackendDBusWrapper ( QObject* parent )
      : QObject ( parent )
  {
    dbus().register_object ( this ).at_session_bus().as ( "/Persistence" );
  }

  // ---------------------------------------------------------------------------------
  bool PersistenceBackendDBusWrapper::persist ( Project & p )
  {
    return persistence().persist ( p ).was_successful();
  }
  // ---------------------------------------------------------------------------------
  bool PersistenceBackendDBusWrapper::persist ( Task & t )
  {
    return persistence().persist ( t ).was_successful();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
