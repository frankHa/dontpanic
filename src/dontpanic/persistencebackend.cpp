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
  success PersistenceBackend::persist ( Project const& _project )
  {
    return _persistence::sqlite().persist ( _project );
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::remove(Project const& _project)
  {
    return _persistence::sqlite().remove(_project);
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persist ( Task const& _t )
  {
    return _persistence::sqlite().persist ( _t );
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persist ( Action const& _a )
  {
    return _persistence::sqlite().persist ( _a );
  }
  // ---------------------------------------------------------------------------------
  Action_ptr PersistenceBackend::activeAction()
  {
    return _persistence::sqlite().activeAction();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
