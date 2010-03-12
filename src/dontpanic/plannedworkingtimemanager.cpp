#include "plannedworkingtimemanager.h"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PlannedWorkingTimeManager::PlannedWorkingTimeManager ( QObject *parent )
      : QObject ( parent )
  {
    init_holidays();
  }
  PlannedWorkingTimeManager::~PlannedWorkingTimeManager()
  {
    delete _M_holidays;
  }
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::store ( WorktimePerDay const& t )
  {
    if ( persistence().persist ( t ).was_successful() )
    {
      emit stored ( t );
    }
  }
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::store ( WorktimePerDayList const& wl )
  {
    foreach ( WorktimePerDay const wt, wl )
    {
      store ( wt );
    }
  }
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::remove ( WorktimePerDay const& t )
  {
    if ( persistence().remove ( t ).was_successful() )
    {
      emit removed ( t );
    }
  }
  // ---------------------------------------------------------------------------------
  WorktimePerDay PlannedWorkingTimeManager::load ( int id )
  {
    WorktimePerDay p ( id );
    if ( persistence().load ( p ).was_successful() )
    {
      return p;
    }
    return NullWorktimePerDay();
  }
  // ---------------------------------------------------------------------------------
  WorktimePerDayList PlannedWorkingTimeManager::findAll()
  {
    WorktimePerDayList list;
    persistence().findAll ( list );
    return list;
  }
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::storeCurrentHolidayRegion ( QString const& r )
  {
    //TODO: needs to be implemented!
    init_holidays();
  }
  // ---------------------------------------------------------------------------------
  QString PlannedWorkingTimeManager::loadCurrentHolidayRegion()
  {
    //TODO: needs to be implemented!
    return "de";
  }
  // ---------------------------------------------------------------------------------
  bool PlannedWorkingTimeManager::isWorkDay ( const QDate& day )
  {
    if ( !_M_holidays->isValid() ) return true;
    return !_M_holidays->isHoliday ( day );
  }

  // ---------------------------------------------------------------------------------
  // private stuff:
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::init_holidays()
  {
    _M_holidays = new KHolidays::HolidayRegion ( loadCurrentHolidayRegion() );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
