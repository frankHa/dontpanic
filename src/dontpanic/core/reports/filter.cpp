/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "filter.h"
#include <libdontpanic/uuid.h>
#include <libdontpanic/action.hpp>
#include <libdontpanic/reporttype.h>
#include <libdontpanic/reportdatafilter.h>
#include <libdontpanic/reportdatafiltertype.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    namespace _filter
    {
      // ---------------------------------------------------------------------------------
      class rule
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual ~rule() {}
          // ---------------------------------------------------------------------------------
          virtual bool matches ( Uuid const& id ) const = 0;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class no_filter_rule: public rule
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual bool matches ( Uuid const& ) const
          {
            return true;
          }
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class selected_filter_rule: public rule
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual bool matches ( Uuid const& id ) const
          {
            return selection.contains ( id );
          }
          // ---------------------------------------------------------------------------------
          void setSelection ( UuidList const ids )
          {
            selection = ids;
          }
          // ---------------------------------------------------------------------------------
          UuidList selection;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class unselected_filter_rule: public selected_filter_rule
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          virtual bool matches ( Uuid const& id ) const
          {
            return !selected_filter_rule::matches ( id );
          }
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class filter_base: public filter
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          filter_base()
              : _M_rule ( new no_filter_rule() ) {}
          // ---------------------------------------------------------------------------------
          virtual ~filter_base() {delete _M_rule;}
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          void set_rule ( rule * r )
          {
            delete _M_rule;
            _M_rule = r;
          }
          // ---------------------------------------------------------------------------------
        protected:
          // ---------------------------------------------------------------------------------
          rule *_M_rule;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class filter_list: public filter
      {
          // ---------------------------------------------------------------------------------
          typedef QList<filter const*> filterlist;
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          ~filter_list() {qDeleteAll ( _M_filters );}
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          void add ( filter const* f )
          {
            _M_filters << f;
          }
          // ---------------------------------------------------------------------------------
          bool matches ( Action const& a ) const
          {
            foreach ( filter const* f, _M_filters )
            {
              if ( !f->matches ( a ) )
              {
                return false;
              }
            }
            return true;
          }
          // ---------------------------------------------------------------------------------
        private:
          filterlist _M_filters;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      class projects_filter: public filter_base
      {
        public:
          bool matches ( Action const& a ) const
          {
            return _M_rule->matches ( a.project() );
          }
      };
      // ---------------------------------------------------------------------------------
      class tasks_filter: public filter_base
      {
        public:
          bool matches ( Action const& a ) const
          {
            return _M_rule->matches ( a.task() );
          }
      };
      // ---------------------------------------------------------------------------------
      class FilterFactory
      {
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          rule *rule_for ( ReportDataFilter const& filter_def )
          {
            rule *result;
            switch ( filter_def.filterType() )
            {
              case ReportDataFilterType::NO_FILTER:
                result = new no_filter_rule(); break;
              case ReportDataFilterType::SELECTED_ONLY:
              {
                selected_filter_rule *tmp = new selected_filter_rule();
                tmp->setSelection ( filter_def.entries() );
                result = tmp;
                break;
              }
              case ReportDataFilterType::UNSELECTED_ONLY:
              {
                unselected_filter_rule *tmp = new unselected_filter_rule();
                tmp->setSelection ( filter_def.entries() );
                result = tmp;
                break;
              }
            }
            return result;
          }
          // ---------------------------------------------------------------------------------
          filter *projects_filter_for ( ReportType const&t )
          {
            filter_base *result = new projects_filter();
            result->set_rule ( rule_for ( t.projectFilter() ) );
            return result;
          }
          // ---------------------------------------------------------------------------------
          filter *tasks_filter_for ( ReportType const&t )
          {
            filter_base *result = new tasks_filter();
            result->set_rule ( rule_for ( t.taskFilter() ) );
            return result;
          }
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          filter* instance_for ( ReportType const& t )
          {
            filter_list *result = new filter_list();
            result->add ( projects_filter_for ( t ) );
            result->add ( tasks_filter_for ( t ) );
            return result;
          }
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
      FilterFactory factory()
      {
        return FilterFactory();
      }
      // ---------------------------------------------------------------------------------
    } //_filter
    // ---------------------------------------------------------------------------------
    filter* filter_for ( ReportType const& t )
    {
      return _filter::factory().instance_for ( t );
    }
    // ---------------------------------------------------------------------------------
  }//reports
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

