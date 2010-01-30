#include "persistencebackend.hpp"

//Qt includes
#include <QDebug>
#include <libdontpanic/action.hpp>
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
  success PersistenceBackend::findAll(ActionList &actions, QDateTime const& from, QDateTime const& to)
  {
    return _persistence::sqlite().findAll(actions, from, to);
  }
  // ---------------------------------------------------------------------------------
  Action PersistenceBackend::lastAction()
  {
    return _persistence::sqlite().lastAction();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
