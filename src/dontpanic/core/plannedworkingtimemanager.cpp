#include "plannedworkingtimemanager.h"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PlannedWorkingTimeManager::PlannedWorkingTimeManager ( QObject *parent )
      : QObject ( parent )
  {
    //init_holidays();
  }
  PlannedWorkingTimeManager::~PlannedWorkingTimeManager()
  {
    //delete _M_holidays;
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
//     if(persistence().persistCurrentHolidayRegion(r).was_successful())
//     {
//       init_holidays();
//       emit currentHolidayRegionChanged(r);
//     }
  }
  // ---------------------------------------------------------------------------------
  QString PlannedWorkingTimeManager::loadCurrentHolidayRegion()
  {
    QString region("");
    //persistence().loadCurrentHolidayRegion(region);
    return region;
  }
  // ---------------------------------------------------------------------------------
  bool PlannedWorkingTimeManager::isWorkDay ( const QDate& day )
  {
    //if ( !_M_holidays->isValid() ) return true;
    //return !_M_holidays->isHoliday ( day );
    return true;
  }

  // ---------------------------------------------------------------------------------
  // private stuff:
  // ---------------------------------------------------------------------------------
  void PlannedWorkingTimeManager::init_holidays()
  {
    //_M_holidays = new KHolidays::HolidayRegion ( loadCurrentHolidayRegion() );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
