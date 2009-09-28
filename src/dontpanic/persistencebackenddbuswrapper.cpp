#include "persistencebackenddbuswrapper.hpp"
#include "persistencebackend.hpp"
#include "libdontpanic/project.hpp"
#include "libdontpanic/dbus.hpp"
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
  bool PersistenceBackendDBusWrapper::persist ( Action & a )
  {
    return persistence().persist ( a ).was_successful();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
