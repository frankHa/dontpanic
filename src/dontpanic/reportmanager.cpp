#include "reportmanager.h"
#include "reports/cfreport.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ReportManager::ReportManager ( QObject *parent )
      : QObject ( parent ){}
  // ---------------------------------------------------------------------------------
  Report ReportManager::generateCfReport(TimeRange const& range)
  {
    return reports::cfreport().setRange(range).asDontPanicReport();    
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
