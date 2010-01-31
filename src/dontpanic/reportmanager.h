#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <QObject>


class QUuid;
namespace dp
{
  // ---------------------------------------------------------------------------------
  class ReportManager: public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      Q_CLASSINFO ( "D-Bus Interface", "org.dontpanic.ReportManager" )
      // ---------------------------------------------------------------------------------
    public slots:
      // ---------------------------------------------------------------------------------
      Report generateCfReport(TimeRange const& time_range);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------      
      ReportManager ( QObject* parent = 0 );
      // ---------------------------------------------------------------------------------            
  };
  // ---------------------------------------------------------------------------------
}
#endif // TIMETRACKER_H
