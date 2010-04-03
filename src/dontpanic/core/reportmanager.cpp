#include "reportmanager.h"
#include "persistencebackend.hpp"
#include "reports/reportgenerator.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ReportManager::ReportManager ( QObject *parent )
      : QObject ( parent ){}
  // ---------------------------------------------------------------------------------
  Report ReportManager::generateReport(ReportType const& _type, TimeRange const& range)
  {
    reports::ReportGenerator report_generator;
    return report_generator.setRange(range).asDontPanicReportOfType(_type);    
  }
  // ---------------------------------------------------------------------------------
  void ReportManager::store ( ReportType const& p )
  {
    if ( persistence().persist ( p ).was_successful() )
    {
      emit stored ( p );
    }
  }
  // ---------------------------------------------------------------------------------
  void ReportManager::remove ( ReportType const& p )
  {
    if ( persistence().remove ( p ).was_successful() )
    {
      emit removed ( p );
    }
  }
  // ---------------------------------------------------------------------------------
  ReportType ReportManager::load ( Uuid const& id )
  {
    ReportType p ( id );
    if ( persistence().load ( p ).was_successful() )
    {
      return p;
    }
    return NullReportType();
  }
  // ---------------------------------------------------------------------------------
  ReportTypeList ReportManager::findAll()
  {
    ReportTypeList list;
    persistence().findAll ( list );
    return list;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
