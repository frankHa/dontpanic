#include "reportgenerator.h"
#include "persistencebackend.hpp"
#include "reports/plannedworkingtime.h"
#include <libdontpanic/action.hpp>
#include <libdontpanic/project.hpp>
#include <libdontpanic/task.hpp>
#include <libdontpanic/durationformatter.h>
#include <memory>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    class GroupingCategory
    {
      public:
        GroupingCategory();
        GroupingCategory ( GroupingCategory *embed );
        virtual ~GroupingCategory();
      public:
        // ---------------------------------------------------------------------------------
        virtual bool matches ( Action const& a ) const = 0;
        // ---------------------------------------------------------------------------------
        virtual void embed ( GroupingCategory *cat );
        // ---------------------------------------------------------------------------------
      protected:
        GroupingCategory *embedded;
    };
    // ---------------------------------------------------------------------------------
    class NullCategory: public GroupingCategory
    {
      public:
        NullCategory() : GroupingCategory ( 0 ) {}
      public:
        bool matches ( Action const& a ) const
        {
          return true;
        }
    };
    // ---------------------------------------------------------------------------------
    class NoGroupingCategory: public GroupingCategory
    {
      public:
        NoGroupingCategory() : GroupingCategory ( 0 ) {}
      public:
        bool matches ( Action const& a ) const
        {
          return false;
        }
    };
    // ---------------------------------------------------------------------------------
    class TaskCategory
          : public GroupingCategory
    {
        // ---------------------------------------------------------------------------------
      public:
        TaskCategory ( Uuid const& t )
            : task ( t ) {}
        // ---------------------------------------------------------------------------------
        bool matches ( Action const&a ) const
        {
          if ( a.task() != task ) {return false;}
          return embedded->matches ( a );
        }
        // ---------------------------------------------------------------------------------
      private:
        Uuid task;
    };
    // ---------------------------------------------------------------------------------
    class ProjectCategory
          : public GroupingCategory
    {
        // ---------------------------------------------------------------------------------
      public:
        ProjectCategory ( Uuid const& p )
            : project ( p ) {}
        // ---------------------------------------------------------------------------------
        bool matches ( Action const&a ) const
        {
          if ( a.project() != project ) {return false;}
          return embedded->matches ( a );
        }
        // ---------------------------------------------------------------------------------
      private:
        Uuid project;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    class group
    {
      public:
        group ( GroupingCategory const* cat );
        ~group ( );
      public:
        //Project project() const;
        //Task task() const;
        int duration() const;
        bool matches ( Action const& a ) const;
        group & add ( Action const& a );

      private:
        GroupingCategory const* category;
        ActionList _M_actions;
    };
    typedef QList<group*> GroupList;
    // ---------------------------------------------------------------------------------
    class group_list
    {
      public:
        group_list ( ReportType const& type );
        ~group_list();
        void sort ( ActionList const& actions );
        QString toString();
      private:
        bool added_to_existing_group ( Action const& a );
        void add_to_newly_created_group ( Action const& a );
        int duration() const;
        QString dump ( group const* g, int dur );
        GroupingCategory * category_for ( Action const& a );
      private:
        ReportType const& _M_type;
        GroupList _M_groups;
    };
    // ---------------------------------------------------------------------------------
    namespace filter
    {

    }
    // ---------------------------------------------------------------------------------
    namespace grouping
    {

    }
    // ---------------------------------------------------------------------------------
    class ReportGeneratorPrivate
    {
      public:
        void setRange ( TimeRange const& r );
        void setType ( ReportType const& type );
        Report asDontPanicReport();
      private:
        QString evaluate ( ActionList const& actions );
      private:
        TimeRange _M_range;
        ReportType _M_type;
    };
    // ---------------------------------------------------------------------------------
    //GroupingCategory impl
    // ---------------------------------------------------------------------------------
    GroupingCategory::GroupingCategory()
        : embedded ( new NullCategory() ) {}
    // ---------------------------------------------------------------------------------
    GroupingCategory::GroupingCategory(GroupingCategory *embed)
        : embedded ( embed ) {}
    // ---------------------------------------------------------------------------------
    GroupingCategory::~GroupingCategory() {delete embedded;}
    // ---------------------------------------------------------------------------------
    void GroupingCategory::embed ( GroupingCategory *cat )
    {
      if ( embedded == 0 )
      {
        embedded = cat;
      }
      else
      {
        embedded->embed ( cat );
      }
    }
    // ---------------------------------------------------------------------------------
    // group impl:
    // ---------------------------------------------------------------------------------
    group::group ( GroupingCategory const* cat )
        : category ( cat ) {}
    // ---------------------------------------------------------------------------------
    group::~group() {delete category;}
    // ---------------------------------------------------------------------------------
    int group::duration() const
    {
      return _M_actions.duration();
    }
    // ---------------------------------------------------------------------------------
    bool group::matches ( Action const& a ) const
    {
      return ( category->matches ( a ) );
    }
    // ---------------------------------------------------------------------------------
    group & group::add ( Action const& a )
    {
      _M_actions.append ( a );
      return *this;
    }
    // ---------------------------------------------------------------------------------
    // group_list
    // ---------------------------------------------------------------------------------
    group_list::group_list ( const dp::ReportType& type )
        : _M_type ( type ) {}
    // ---------------------------------------------------------------------------------
    group_list::~group_list()
    {
      qDeleteAll ( _M_groups );
    }
    // ---------------------------------------------------------------------------------
    bool group_list::added_to_existing_group ( Action const& a )
    {
      foreach ( group *g, _M_groups )
      {
        if ( g->matches ( a ) )
        {
          g->add ( a );
          return true;
        }
      }
      return false;
    }
    // ---------------------------------------------------------------------------------
    void group_list::add_to_newly_created_group ( Action const& a )
    {
      group *g = new group ( category_for ( a ) );
      g->add ( a );
      _M_groups << g;
    }
    // ---------------------------------------------------------------------------------
    GroupingCategory* group_list::category_for ( const dp::Action& a )
    {
      GroupingCategory *result = 0;
      if ( _M_type.groupByTask() )
      {
        result = new TaskCategory ( a.task() );
      }
      if ( _M_type.groupByProject() )
      {
        GroupingCategory *project = new ProjectCategory ( a.project() );
        if ( result == 0 )
        {
          result = project;
        }
        else
        {
          result->embed ( project );
        }
      }
      if ( result == 0 )
      {
        result = new NoGroupingCategory();
      }
      return result;
    }
    // ---------------------------------------------------------------------------------
    void group_list::sort ( ActionList const& actions )
    {
      foreach ( Action const& action, actions )
      {
        if ( !added_to_existing_group ( action ) )
        {
          add_to_newly_created_group ( action );
        }
      }
    }
    // ---------------------------------------------------------------------------------
    int group_list::duration() const
    {
      int result ( 0 );
      foreach ( group *g, _M_groups )
      {
        result += g->duration();
      }
      return result;
    }
    // ---------------------------------------------------------------------------------
    QString group_list::dump ( group const* g, int dur )
    {
      double percentage = 0.0;
      DurationFormatter formatter;
      if ( dur != 0 ) {percentage = 100.0 * ( double ) g->duration() / ( double ) dur;}
      //Project const& p = g->project();
      QString s = QString ( "%1;%2" )
                  //.arg ( g->task().name() )
                  //.arg ( p.name() )
                  .arg ( formatter.format ( g->duration() ) )
                  .arg ( percentage, 0, 'f', 2 )
                  //.arg ( p.comment() )
                  ;
      return s;

    }
    // ---------------------------------------------------------------------------------
    QString group_list::toString()
    {
      //QString result= "Typ;Projekt;Dauer (Tätigkeitsgruppe);Prozent (Tätigkeitsgruppe);Projektkommentar\n";
      QString result = i18n ( "Work Type;Project;Duration (Activity Group);Percent (Activity Group);Project Comment\n" );
      int complete_duration = duration();
      foreach ( group *g, _M_groups )
      {
        result += dump ( g, complete_duration ) + "\n";
      }
      return result;
    }
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
    QString ReportGeneratorPrivate::evaluate ( ActionList const& actions )
    {
      group_list gl ( _M_type );
      gl.sort ( actions );
      QString const& result = gl.toString();
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

