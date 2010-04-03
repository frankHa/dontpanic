#include "persistencebackend.hpp"

//Qt includes
#include <QDebug>
#include <libdontpanic/action.hpp>
#include <kglobal.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  K_GLOBAL_STATIC(PersistenceBackend, _instance);
  // ---------------------------------------------------------------------------------  
  PersistenceBackend & persistence()
  {
    return *_instance;
  }
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
  bool PersistenceBackend::hasActionsFor(QDate const& date)
  {
    return _persistence::sqlite().hasActionsFor(date);
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::persistCurrentHolidayRegion(QString const& region) const
  {
    return _persistence::sqlite().persistCurrentHolidayRegion(region);
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::removeCurrentHolidayRegion() const
  {
    return _persistence::sqlite().removeCurrentHolidayRegion();
  }
  // ---------------------------------------------------------------------------------
  success PersistenceBackend::loadCurrentHolidayRegion(QString & region) const
  {
    return _persistence::sqlite().loadCurrentHolidayRegion(region);
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
