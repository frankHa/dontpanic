#include "PersistanceBackendDBusWrapper.hpp"
#include "PersistanceBackend.hpp"
#include "libdontpanic/Project.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  bool PersistanceBackendDBusWrapper::persist (Project & p)
  {
    return persistance().persist(p).was_successful();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
