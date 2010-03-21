#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/report.h>
#include <libdontpanic/reporttype.h>
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
    signals:
      // ---------------------------------------------------------------------------------
      void removed ( dp::ReportType );
      void stored ( dp::ReportType );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      ReportManager ( QObject *parent = 0 );
      // ---------------------------------------------------------------------------------
    public slots:
      // ---------------------------------------------------------------------------------
      Report generateCfReport(TimeRange const& time_range);
      // ---------------------------------------------------------------------------------
      void store ( ReportType const& p );
      // ---------------------------------------------------------------------------------
      void remove ( ReportType const& p );
      // ---------------------------------------------------------------------------------
      ReportType load ( Uuid const& p );
      // ---------------------------------------------------------------------------------
      ReportTypeList findAll();
      // ---------------------------------------------------------------------------------          
  };
  // ---------------------------------------------------------------------------------
}
#endif // REPORTMANAGER_H
