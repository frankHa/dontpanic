#ifndef DP_REPORTS_GROUP_H
#define DP_REPORTS_GROUP_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <libdontpanic/action.hpp>
#include <libdontpanic/reporttype.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    namespace grouping
    {
      class category;
    }
    // ---------------------------------------------------------------------------------
    class group
    {
      public:
        group ( grouping::category const* cat );
        ~group ( );
      public:
        int duration() const;
        bool matches ( Action const& a ) const;
        group & add ( Action const& a );
        Action first() const;

      private:
        grouping::category const* _M_category;
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
        //QString toString();
        ReportType report_type() const;
        int duration() const;     
        GroupList const& groups()const;
        // ---------------------------------------------------------------------------------
      private:
        bool added_to_existing_group ( Action const& a );
        void add_to_newly_created_group ( Action const& a );
        grouping::category * category_for ( Action const& a );
      private:
        ReportType const& _M_type;
        GroupList _M_groups;
    };

    // ---------------------------------------------------------------------------------
  }//reports
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif
