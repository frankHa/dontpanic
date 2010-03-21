#ifndef DP__PERSISTENCE__SQLITE_ACTION_H
#define DP__PERSISTENCE__SQLITE_ACTION_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/success.hpp>
#include <libdontpanic/action.hpp>
class QSqlQuery;
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      class Action
      {
          // ---------------------------------------------------------------------------------
        public:
          // ---------------------------------------------------------------------------------
          success create_table() const;
          // ---------------------------------------------------------------------------------
          success persist ( dp::Action const&p ) const;
          // ---------------------------------------------------------------------------------
          success load ( dp::Action &p ) const;
          // ---------------------------------------------------------------------------------
          success remove ( dp::Action const&p ) const;
          // ---------------------------------------------------------------------------------
          success findAll(dp::ActionList &l, QDateTime const& from, QDateTime const& to) const;
          // ---------------------------------------------------------------------------------
          dp::Action findLastAction() const;
          // ---------------------------------------------------------------------------------
          bool hasActionFor(QDate const& date) const;
          // ---------------------------------------------------------------------------------
          bool hasActionFor(QDateTime const& from, QDateTime const& to) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          bool exists ( dp::Action const& _project ) const;
          // ---------------------------------------------------------------------------------
          success insert ( dp::Action const&_p ) const;
          // ---------------------------------------------------------------------------------
          success update ( dp::Action const& _p ) const;
          // ---------------------------------------------------------------------------------
          success assign_query_values_to_entity ( QSqlQuery &query, dp::Action &p ) const;
          // ---------------------------------------------------------------------------------
      };//Project
      // ---------------------------------------------------------------------------------
      inline Action action()
      {
        return Action();
      }
      // ---------------------------------------------------------------------------------
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP__PERSISTENCE__SQLITE_ACTION_H
