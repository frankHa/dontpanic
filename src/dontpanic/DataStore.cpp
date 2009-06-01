#include "DataStore.hpp"
#include "Sqlite.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  success DataStore::persist ( Project& _project )
  {
    return sqlite().persist(_project);
  }

  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
