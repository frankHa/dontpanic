#include "group.h"
#include "category.h"
#include "filter.h"
#include <libdontpanic/durationformatter.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    // group impl:
    // ---------------------------------------------------------------------------------
    group::group ( grouping::category const* cat )
        : _M_category ( cat ) {}
    // ---------------------------------------------------------------------------------
    group::~group() {delete _M_category;}
    // ---------------------------------------------------------------------------------
    int group::duration() const
    {
      return _M_actions.duration();
    }
    // ---------------------------------------------------------------------------------
    bool group::matches ( Action const& a ) const
    {
      return ( _M_category->matches ( a ) );
    }
    // ---------------------------------------------------------------------------------
    group & group::add ( Action const& a )
    {
      _M_actions.append ( a );
      return *this;
    }
    // ---------------------------------------------------------------------------------
    Action group::first() const
    {
      if ( _M_actions.size() == 0 ) {return NullAction();}
      return _M_actions.value ( 0 );
    }
    // ---------------------------------------------------------------------------------
    // group_list
    // ---------------------------------------------------------------------------------
    group_list::group_list ( const dp::ReportType& type )
        : _M_type ( type )
        , _M_filter ( 0 ) {}
    // ---------------------------------------------------------------------------------
    group_list::~group_list()
    {
      qDeleteAll ( _M_groups );
      delete _M_filter;
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
    grouping::category* group_list::category_for ( const dp::Action& a )
    {
      grouping::category *result = 0;
      if ( _M_type.groupByTask() )
      {
        result = new grouping::task ( a.task() );
      }
      if ( _M_type.groupByProject() )
      {
        grouping::category *p = new grouping::project ( a.project() );
        if ( result == 0 )
        {
          result = p;
        }
        else
        {
          result->embed ( p );
        }
      }
      if ( result == 0 )
      {
        result = new grouping::no();
      }
      return result;
    }
    // ---------------------------------------------------------------------------------
    void group_list::sort ( ActionList const& actions )
    {
      init_filter();
      foreach ( Action const& action, actions )
      {
        if ( _M_filter->matches ( action ) )
        {
          if ( !added_to_existing_group ( action ) )
          {
            add_to_newly_created_group ( action );
          }
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
    ReportType group_list::report_type() const
    {
      return _M_type;
    }
    GroupList const& group_list::groups() const
    {
      return _M_groups;
    }
    // ---------------------------------------------------------------------------------
    void group_list::init_filter()
    {
      delete _M_filter;
      _M_filter = filter_for(report_type());
    }
    // ---------------------------------------------------------------------------------
  }//reports
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
