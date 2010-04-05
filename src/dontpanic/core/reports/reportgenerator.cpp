#include "reportgenerator.h"
#include "category.h"
#include "group.h"
#include "columns.h"
#include "persistencebackend.hpp"
#include "reports/plannedworkingtime.h"
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    class ReportGeneratorPrivate
    {
      public:
        void setRange ( TimeRange const& r );
        void setType ( ReportType const& type );
        Report asDontPanicReport();
      private:
        ReportData evaluate ( ActionList const& actions );
      private:
        TimeRange _M_range;
        ReportType _M_type;
        Columns _M_columns;
    };
    // ---------------------------------------------------------------------------------
    // ReportGeneratorPrivate imp:
    // ---------------------------------------------------------------------------------
    void ReportGeneratorPrivate::setRange ( TimeRange const& r )
    {
      _M_range = r;
    }
    // ---------------------------------------------------------------------------------
    Report ReportGeneratorPrivate::asDontPanicReport()
    {
      Report report;
      report.setReportType ( _M_type ).setRange ( _M_range );
      ActionList actions;
      if ( persistence().findAll ( actions, _M_range.from(), _M_range.to() ).has_failed() )
      {
        return report.setValid ( false );
      }
      return report.setReportData ( evaluate ( actions ) ).setDuration ( actions.duration() ).setPlannedWorkingTime ( planned_working_time_for ( _M_range ) );
    }
    // ---------------------------------------------------------------------------------
    void ReportGeneratorPrivate::setType ( const dp::ReportType& type )
    {
      _M_type = type;
    }
    // ---------------------------------------------------------------------------------
    ReportData ReportGeneratorPrivate::evaluate ( ActionList const& actions )
    {
      group_list gl ( _M_type );
      gl.sort ( actions );
      ReportData result = _M_columns.dump(gl);
      return result;
    }
    // ---------------------------------------------------------------------------------
    // ReportGenerator:
    // ---------------------------------------------------------------------------------
    ReportGenerator::ReportGenerator()
        : d_ptr ( new ReportGeneratorPrivate() ) {}
    // ---------------------------------------------------------------------------------
    ReportGenerator::~ReportGenerator()
    {
      delete d_ptr;
    }
    // ---------------------------------------------------------------------------------
    ReportGenerator & ReportGenerator::setRange ( TimeRange const& range )
    {
      Q_D ( ReportGenerator );
      d->setRange ( range );
      return *this;
    }
    // ---------------------------------------------------------------------------------
    Report ReportGenerator::asDontPanicReportOfType ( ReportType const&rt )
    {
      Q_D ( ReportGenerator );
      d->setType ( rt );
      return d->asDontPanicReport();
    }
  } // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

