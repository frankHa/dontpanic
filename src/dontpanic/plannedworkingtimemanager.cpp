#include "plannedworkingtimemanager.h"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  PlannedWorkingTimeManager::PlannedWorkingTimeManager ( QObject *parent )
      : QObject ( parent ){}
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
    foreach(WorktimePerDay const wt, wl)
    {
      store(wt);
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
}//dp
// ---------------------------------------------------------------------------------
