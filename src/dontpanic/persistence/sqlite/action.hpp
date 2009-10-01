#ifndef DP__PERSISTENCE__SQLITE_ACTION_H
#define DP__PERSISTENCE__SQLITE_ACTION_H

#include <defines.hpp>
#include <libdontpanic/success.hpp>

class QSqlQuery;
namespace dp
{
  // ---------------------------------------------------------------------------------
  class Action;
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
          success persist ( dp::Action &p ) const;
          // ---------------------------------------------------------------------------------
          success load ( dp::Action &p ) const;
          // ---------------------------------------------------------------------------------
        private:
          // ---------------------------------------------------------------------------------
          bool exists ( dp::Action const& _project ) const;
          // ---------------------------------------------------------------------------------
          success insert ( dp::Action &_p ) const;
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