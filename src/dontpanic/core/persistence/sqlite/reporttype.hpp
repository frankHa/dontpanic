#ifndef DP_PERSISTANCE_SQLITE_REPORTTYPE_HPP
#define DP_PERSISTANCE_SQLITE_REPORTTYPE_HPP
// ---------------------------------------------------------------------------------
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/success.hpp"
//Forward decl
class QSqlQuery;
// ---------------------------------------------------------------------------------
namespace dp
{
  class ReportType;
  typedef QList<ReportType> ReportTypeList;
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      class ReportType
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          success create_table();
          // ---------------------------------------------------------------------------------
          success persist ( dp::ReportType const&p ) const;
          // ---------------------------------------------------------------------------------
          success remove ( dp::ReportType const&p ) const;
          // ---------------------------------------------------------------------------------
          success load ( dp::ReportType &p ) const;
          // ---------------------------------------------------------------------------------
          success findAll ( dp::ReportTypeList &list ) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          success create_project_filter_table() const;
          // ---------------------------------------------------------------------------------
          success create_task_filter_table() const; 
          // ---------------------------------------------------------------------------------
          success create_email_recipients_table() const;
          // ---------------------------------------------------------------------------------
          bool exists ( dp::ReportType const& _project ) const;
          // ---------------------------------------------------------------------------------
          success insert ( dp::ReportType const&_p ) const;
          // ---------------------------------------------------------------------------------
          success update ( dp::ReportType const& _p ) const;
          // ---------------------------------------------------------------------------------
          success load_selected_projects( dp::ReportType & _p) const;
          // ---------------------------------------------------------------------------------
          success load_selected_tasks( dp::ReportType & _p) const;
          // ---------------------------------------------------------------------------------
          success load_selected_email_recipients( dp::ReportType & _p) const;
          // ---------------------------------------------------------------------------------
          success update_selected_projects ( dp::ReportType const& _p ) const;
          // ---------------------------------------------------------------------------------
          success update_selected_tasks ( dp::ReportType const& _p ) const;
          // ---------------------------------------------------------------------------------
          success update_selected_email_recipients( dp::ReportType const& _p) const;
          // ---------------------------------------------------------------------------------
          success remove_selected_projects(dp::ReportType const& _p) const;
          // ---------------------------------------------------------------------------------
          success remove_selected_tasks(dp::ReportType const& _p) const;
          // ---------------------------------------------------------------------------------
          success remove_selected_email_recipients( dp::ReportType const& _p) const;
          // ---------------------------------------------------------------------------------
          success assign_query_values_to_entity ( QSqlQuery &query, dp::ReportType &p ) const;
          // ---------------------------------------------------------------------------------
      };//Project
      // ---------------------------------------------------------------------------------
      inline ReportType report_type()
      {
        return ReportType();
      }
      // ---------------------------------------------------------------------------------
    }//_sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //!DP_PERSISTANCE_SQLITE_REPORTTYPE_HPP
