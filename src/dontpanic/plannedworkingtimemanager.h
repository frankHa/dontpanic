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
    public slots:
      // ---------------------------------------------------------------------------------
      
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------      
      PlannedWorkingTimeManager ( QObject* parent = 0 );
      // ---------------------------------------------------------------------------------            
  };
  // ---------------------------------------------------------------------------------
}
#endif // PLANNED_WORKING_TIME_MANAGER_H
