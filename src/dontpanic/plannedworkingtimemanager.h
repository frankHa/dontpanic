#ifndef PLANNED_WORKING_TIME_MANAGER_H
#define PLANNED_WORKING_TIME_MANAGER_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/worktimeperday.h>
#include <QObject>
#include <kholidays/holidays.h>


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
      void currentHolidayRegionStored(QString);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      PlannedWorkingTimeManager ( QObject *parent = 0 );
      // ---------------------------------------------------------------------------------
      ~PlannedWorkingTimeManager();
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
      void storeCurrentHolidayRegion(QString const& r);
      // ---------------------------------------------------------------------------------
      QString loadCurrentHolidayRegion();
      // ---------------------------------------------------------------------------------
      bool isWorkDay(QDate const& day);
      // ---------------------------------------------------------------------------------
      WorktimePerDayList findAll();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      void init_holidays();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      KHolidays::HolidayRegion *_M_holidays;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
#endif // PLANNED_WORKING_TIME_MANAGER_H
