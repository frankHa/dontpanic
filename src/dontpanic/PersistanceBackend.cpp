#include "PersistanceBackend.hpp"
#include "persistance/Sqlite.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  success PersistanceBackend::persist ( Project& _project )
  {
    return sqlite().persist(_project);
  }

  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------