#include "columns.h"
#include "group.h"
#include "context.h"
#include <libdontpanic/uuid.h>
#include <libdontpanic/durationformatter.h>
#include <libdontpanic/action.hpp>
#include <libdontpanic/reporttype.h>
#include <QVariant>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    namespace columns
    {
      // ---------------------------------------------------------------------------------
      namespace detail
      {
        QString percentage(int overall, int duration)
        {
          double percentage = 0.0;
          if ( overall != 0 ) {percentage = 100.0 * ( double ) duration / ( double ) overall;}
          return QString("%1%").arg ( percentage, 0, 'f', 2 );
        }
      }
      // ---------------------------------------------------------------------------------
      class column
      {
        public:
          virtual ~column() {}
        public:
          virtual QString name() const = 0;
          virtual QVariant value_of ( group const*g ) const = 0;
      };
      // ---------------------------------------------------------------------------------
      class date: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return t.groupByTimeInterval() == ReportType::DAILY;
          }
          virtual QString name() const
          {
            return i18n ( "Date" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return a.startTime().date();
          }
      };
      // ---------------------------------------------------------------------------------
      class week: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return t.groupByTimeInterval() == ReportType::WEEKLY;
          }
          virtual QString name() const
          {
            return i18n ( "Week" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return a.startTime().date().weekNumber();
          }
      };
      // ---------------------------------------------------------------------------------
      class month: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return t.groupByTimeInterval() == ReportType::MONTHLY;
          }
          virtual QString name() const
          {
            return i18n ( "Month" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return a.startTime().date().month();
          }
      };
      // ---------------------------------------------------------------------------------
      class quarter: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return t.groupByTimeInterval() == ReportType::QUARTERLY;
          }
          virtual QString name() const
          {
            return i18n ( "Quarter" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            int month = a.startTime().date().month();
            if ( month < 4 ) return 1;
            if ( month < 7 ) return 2;
            if ( month < 10 ) return 3;
            return 4;
          }
      };
      // ---------------------------------------------------------------------------------
      class year: public column
      {
        public:
          year ( ReportType const& t ) : _M_report_type ( t ) {}
        public:
          static bool applies_to ( ReportType const& t )
          {
            int tg = t.groupByTimeInterval();
            return ( tg == ReportType::WEEKLY || tg == ReportType::MONTHLY || tg == ReportType::QUARTERLY );
          }
          virtual QString name() const
          {
            return i18n ( "Year" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            if ( _M_report_type.groupByTimeInterval() != ReportType::WEEKLY )
            {
              return a.startTime().date().month();
            }
            int year;
            a.startTime().date().weekNumber ( &year );
            return year;
          }
          ReportType _M_report_type;
      };
      // ---------------------------------------------------------------------------------
      class work_type: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() || t.groupByTask() );
          }
          virtual QString name() const
          {
            return i18n ( "Work Type" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return context()->taskManager()->load ( a.task() ).name();
          }
      };
      // ---------------------------------------------------------------------------------
      class project: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() || t.groupByProject() );
          }
          virtual QString name() const
          {
            return i18n ( "Project" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return context()->projectManager()->load ( a.project() ).name();
          }
      };
      // ---------------------------------------------------------------------------------
      class from: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "From" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return a.startTime();
          }
      };
      // ---------------------------------------------------------------------------------
      class to: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "To" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return a.endTime();
          }
      };
      // ---------------------------------------------------------------------------------
      class duration_group: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( !t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "Duration (Activity Group)" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            return duration_formatter().format ( g->duration() );
          }
      };
      // ---------------------------------------------------------------------------------
      class duration: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "Duration" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return duration_formatter().format ( a.duration() );
          }
      };
      // ---------------------------------------------------------------------------------
      class percentage_group: public column
      {
        public:
          percentage_group(int overall_duration):_M_overall(overall_duration){}
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( !t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "Percentage (Activity Group)" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            return detail::percentage(_M_overall, g->duration());
          }
          
          int _M_overall;
      };
      // ---------------------------------------------------------------------------------
      class percentage: public column
      {
        public:
          percentage(int overall_duration):_M_overall(overall_duration){}
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() );
          }
          virtual QString name() const
          {
            return i18n ( "Percentage" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            return detail::percentage(_M_overall, g->duration());
          }
          
          int _M_overall;
      };
      // ---------------------------------------------------------------------------------
      class project_comment: public column
      {
        public:
          static bool applies_to ( ReportType const& t )
          {
            return ( t.noGrouping() || t.groupByProject() );
          }
          virtual QString name() const
          {
            return i18n ( "Project Comment" );
          }
          virtual QVariant value_of ( group const*g ) const
          {
            Action const& a = g->first();
            if ( !a.isValid() ) return "";
            return context()->projectManager()->load ( a.project() ).comment();
          }
      };
      // ---------------------------------------------------------------------------------
    }// column
    // ---------------------------------------------------------------------------------
    //Columns impl:
    // ---------------------------------------------------------------------------------
    Columns::~Columns()
    {
      qDeleteAll(_M_columns);
    }
    // ---------------------------------------------------------------------------------
    ReportData Columns::dump(group_list const& gl)
    {
      init(gl);     
      
      ReportData result;
      set_headers(result);
      foreach(group const* g, gl.groups())
      {
        add_group(result, g);
      }
      return result;
    }
    // ---------------------------------------------------------------------------------
    void Columns::set_headers(ReportData &data) const
    {
      foreach(columns::column const* col, _M_columns)
      {
        data.addHeader(col->name());
      }
    }
    // ---------------------------------------------------------------------------------
    void Columns::add_group(ReportData &data, group const*g) const
    {
      ReportData::Row row;
      foreach(columns::column const* col, _M_columns)
      {
        row.append(col->value_of(g));
      }
      data.addRow(row);
    }
    // ---------------------------------------------------------------------------------
    //private stuff:
    // ---------------------------------------------------------------------------------
    void Columns::init(group_list const& gl)
    {
      ReportType const&t = gl.report_type();
      if(columns::date::applies_to(t))
      {
        _M_columns.append(new columns::date());
      }
      if(columns::week::applies_to(t))
      {
        _M_columns.append(new columns::week());
      }
      if(columns::month::applies_to(t))
      {
        _M_columns.append(new columns::month());
      }
      if(columns::quarter::applies_to(t))
      {
        _M_columns.append(new columns::quarter());
      }
      if(columns::year::applies_to(t))
      {
        _M_columns.append(new columns::year(t));
      }
      if(columns::work_type::applies_to(t))
      {
        _M_columns.append(new columns::work_type());
      }
      if(columns::project::applies_to(t))
      {
        _M_columns.append(new columns::project());
      }
      if(columns::from::applies_to(t))
      {
        _M_columns.append(new columns::from());
      }
      if(columns::to::applies_to(t))
      {
        _M_columns.append(new columns::to());
      }
      if(columns::duration_group::applies_to(t))
      {
        _M_columns.append(new columns::duration_group());
      }
      if(columns::duration::applies_to(t))
      {
        _M_columns.append(new columns::duration());
      }
      if(columns::percentage_group::applies_to(t))
      {
        _M_columns.append(new columns::percentage_group(gl.duration()));
      }
      if(columns::percentage::applies_to(t))
      {
        _M_columns.append(new columns::percentage(gl.duration()));
      }
      if(columns::project_comment::applies_to(t))
      {
        _M_columns.append(new columns::project_comment());
      }
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------