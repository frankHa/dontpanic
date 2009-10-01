#include "persistence/sqlite/task.hpp"
#include "libdontpanic/task.hpp"
#include "persistence/execute_query.hpp"
//Qt includes
#include <QVariant>
// ---------------------------------------------------------------------------------
// inserting table rows:
// ---------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      const QString INSERT_TASK =
        "INSERT INTO t_task(t_id, t_name, t_visible, t_solo_effort, t_chargeable, t_creation_date)VALUES(?, ?, ?, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_TASKS =
        "SELECT t_name, t_visible, t_solo_effort, t_chargeable, t_creation_date FROM t_task";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_VISIBLE_TASKS =
        SELECT_ALL_TASKS + " WHERE (t_visible <> 0)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_TASK =
        "SELECT DISTINCT t_name, t_visible, t_solo_effort, t_chargeable, t_creation_date FROM t_task WHERE (t_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_TASK =
        "UPDATE p_project set t_name=?, t_visible=?, t_solo_effort=?, t_chargeable=?, t_creation_date=? WHERE (t_id=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success Task::persist ( dp::Task &_project ) const
      {
        if ( exists ( _project ) )
        {
          return update ( _project );
        }
        return insert ( _project );
      }
      // ---------------------------------------------------------------------------------
      success Task::load ( dp::Task &t ) const
      {
        if ( t.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_TASK );
        query.addBindValue ( t.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        if ( !query.first() )
        {
          return error();
        }
        return assign_query_values_to_entity ( query, t );
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool Task::exists ( const dp::Task& _task ) const
      {
        if ( _task.id().isNull() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_TASK );
        query.addBindValue ( _task.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success Task::insert ( dp::Task& _t ) const
      {
        QSqlQuery query;
        query.prepare ( INSERT_TASK );
        query.addBindValue ( _t.id().toString() );
        query.addBindValue ( _t.name() );
        query.addBindValue ( _t.is_visible() );
        query.addBindValue ( _t.is_solo_effort() );
        query.addBindValue ( _t.is_chargeable() );
        query.addBindValue ( _t.creation_date() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success Task::update ( const dp::Task& _t ) const
      {
        if(_t.id().isNull())
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_TASK );
        query.addBindValue ( _t.name() );
        query.addBindValue ( _t.is_visible() );
        query.addBindValue ( _t.is_solo_effort() );
        query.addBindValue ( _t.is_chargeable() );
        query.addBindValue ( _t.creation_date() );
        query.addBindValue ( _t.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success Task::assign_query_values_to_entity ( QSqlQuery& query, dp::Task& t ) const
      {
        t.set_name ( query.value ( 1 ).toString() );
        t.set_is_visible ( query.value ( 2 ).toBool() );
        t.set_is_solo_effort ( query.value ( 3 ).toBool() );
        t.set_is_chargeable ( query.value ( 4 ).toBool() );
        t.set_creation_date ( query.value ( 5 ).toDateTime() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
