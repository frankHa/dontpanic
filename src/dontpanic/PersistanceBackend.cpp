#include "PersistanceBackend.hpp"
#include "persistance/Sqlite.hpp"

//Qt includes
#include <QDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  bool PersistanceBackend::init()
  {
    if ( dp::_persistance::sqlite().open_database_connection().has_failed() )
    {
      qWarning() << "unable to initialize persistance backend. exiting now";
      ::exit ( 1 );
    }
    if ( dp::_persistance::sqlite().update_database_schema_if_necessary().has_failed() )
    {
      qWarning() << "unable to initialize the required database schema. exiting now";
      ::exit ( 1 );
    }
    return true;
  }
  // ---------------------------------------------------------------------------------
  success PersistanceBackend::persist ( Project& _project )
  {
    return _persistance::sqlite().persist ( _project );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
