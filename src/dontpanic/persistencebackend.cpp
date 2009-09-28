#include "persistencebackend.hpp"
#include "persistence/sqlite.hpp"

//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  bool PersistenceBackend::init()
  {
    if ( dp::_persistence::sqlite().open_database_connection().has_failed() )
    {
      qWarning() << "unable to initialize persistance backend. exiting now";
      ::exit ( 1 );
    }
    if ( dp::_persistence::sqlite().update_database_schema_if_necessary().has_failed() )
    {
      qWarning() << "unable to initialize the required database schema. exiting now";
      ::exit ( 1 );
    }
    return true;
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persist ( Project& _project )
  {
    return _persistence::sqlite().persist ( _project );
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persist ( Task& _t )
  {
    return _persistence::sqlite().persist ( _t );
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persist ( Action& _a )
  {
    return _persistence::sqlite().persist ( _a );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
