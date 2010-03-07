#ifndef PLANNED_WORKING_TIME_MANAGER_H
#define PLANNED_WORKING_TIME_MANAGER_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/worktimeperday.h>
#include <QObject>


namespace dp
{
  // ---------------------------------------------------------------------------------
  class PlannedWorkingTimeManager
  : public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      Q_CLASSINFO ( "D-Bus Interface", "org.dontpanic.PlannedWorkingTimeManager" )
      // ---------------------------------------------------------------------------------
    signals:
      void removed ( dp::WorktimePerDay );
      void stored ( dp::WorktimePerDay );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      PlannedWorkingTimeManager ( QObject *parent = 0 );
      // ---------------------------------------------------------------------------------
    public slots:
      // ---------------------------------------------------------------------------------
      WorktimePerDay load ( int );
      // ---------------------------------------------------------------------------------
      void store ( WorktimePerDay const& p );
      // ---------------------------------------------------------------------------------
      void store ( WorktimePerDayList const& p );
      // ---------------------------------------------------------------------------------
      void remove ( WorktimePerDay const& p );
      // ---------------------------------------------------------------------------------
      WorktimePerDayList findAll();
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
#endif // PLANNED_WORKING_TIME_MANAGER_H
