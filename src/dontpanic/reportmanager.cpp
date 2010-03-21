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
    reports::CFReport cfrep;
    return cfrep.setRange(range).asDontPanicReport();    
  }
  // ---------------------------------------------------------------------------------
  void ReportManager::store ( ReportType const& p )
  {
  }
  // ---------------------------------------------------------------------------------
  void ReportManager::remove ( ReportType const& p )
  {
  }
  // ---------------------------------------------------------------------------------
  ReportType ReportManager::load ( Uuid const& p )
  {
    ReportType t("cf monthly");
    return t;
  }
  // ---------------------------------------------------------------------------------
  ReportTypeList ReportManager::findAll()
  {
    ReportTypeList list;
    list<<load(Uuid());
    return list;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
