#include <persistence/sqlite/action.hpp>
#include "persistence/execute_query.hpp"
#include <libdontpanic/action.hpp>

#include <persistence/sqlite/task.hpp>
#include <persistence/sqlite/project.hpp>
#include <QVariant>
#include <QSqlQuery>
#include <KDebug>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      const QString INSERT_ACTION =
        "INSERT INTO a_action(a_id, a_t_task , a_p_project,a_ct_collaboration_type,\
        a_name, a_comment, a_start, a_end, a_reviewed, a_billed)VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_ACTIONS =
        "SELECT a_id, a_t_task , a_p_project,a_ct_collaboration_type,\
        a_name, a_comment, a_start, a_end, a_reviewed, a_billed FROM a_action";
        
      const QString SELECT_RANGE_OF_ACTIONS =
        "SELECT a_id, a_t_task , a_p_project,a_ct_collaboration_type,\
        a_name, a_comment, a_start, a_end, a_reviewed, a_billed FROM a_action \
        WHERE a_start>=? AND a_start<?";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_ACTION =
        "SELECT DISTINCT a_t_task , a_p_project,a_ct_collaboration_type,\
        a_name, a_comment, a_start, a_end, a_reviewed, a_billed FROM a_action WHERE (a_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_ACTION =
        "UPDATE a_action set a_t_task=?, a_p_project=?,a_ct_collaboration_type=?,\
        a_name=?, a_comment=?, a_start=?, a_end=?, a_reviewed=?, a_billed=? WHERE (a_id=?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ACTIVE = "SELECT a_id FROM A_ACTION WHERE (a_end = 'NULL')";
      // ---------------------------------------------------------------------------------
      success Action::persist ( dp::Action const&_a ) const
      {
        if ( exists ( _a ) )
        {
          return update ( _a );
        }
        return insert ( _a );
      }
      // ---------------------------------------------------------------------------------
      success Action::load ( dp::Action &a ) const
      {
        if ( a.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_ACTION );
        query.addBindValue ( a.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        if ( !query.first() )
        {
          return error();
        }
        return assign_query_values_to_entity ( query, a );
      }
      // ---------------------------------------------------------------------------------
      success Action::findAll ( dp::ActionList &l, QDateTime const& from, QDateTime const& to ) const
      {
        kDebug()<<"from: "<<from<<" to: "<<to;
        QSqlQuery query;
        query.prepare(SELECT_RANGE_OF_ACTIONS);
        bindTimeValue ( query, from );
        bindTimeValue ( query, to );
        if ( execute ( query ).has_failed() )
        {
          kWarning()<<"last error: "<<query.lastError();
          return error();
        }
        while ( query.next() )
        {
          dp::Action _a(QUuid(query.value(0).toString()));
          assign_query_values_to_entity(query, _a);
          l.append(_a);
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      dp::Action Action::findActive() const
      {
        QSqlQuery query;
        query.prepare ( SELECT_ACTIVE );
        if ( execute ( query ).has_failed() )
        {
          qWarning() << "query SELECT_ACTIVE failed";
          return dp::NullAction();
        }
        if ( !query.first() )
        {
          qWarning() << "no active action found";
          return dp::NullAction();
        }
        QUuid const&id = query.value ( 0 ).toString();
        dp::Action _a ( id );
        if ( load ( _a ).has_failed() )
        {
          qWarning() << "loading the active action [" << id.toString() << "]has failed";
        }
        return _a;
      }
      // ---------------------------------------------------------------------------------
      //private stuff:
      // ---------------------------------------------------------------------------------
      bool Action::exists ( dp::Action const& _a ) const
      {
        if ( _a.id().isNull() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_ACTION );
        query.addBindValue ( _a.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success Action::insert ( dp::Action const&_a ) const
      {
        {
          if ( _a.id().isNull() )
          {
            return error();
          }
          QSqlQuery query;
          query.prepare ( INSERT_ACTION );
          query.addBindValue ( _a.id().toString() );
          query.addBindValue ( _a.task().toString() );
          query.addBindValue ( _a.project().toString() );
          query.addBindValue ( _a.collaborationType().toString() );
          query.addBindValue ( _a.name() );
          query.addBindValue ( _a.comment() );
          bindTimeValue ( query, _a.startTime() );
          bindTimeValue ( query, _a.endTime() );
          query.addBindValue ( _a.reviewed() );
          query.addBindValue ( _a.billed() );
          if ( execute ( query ).has_failed() )
          {
            return error();
          }
          return successful();
        }
      }
      // ---------------------------------------------------------------------------------
      success Action::update ( dp::Action const& _a ) const
      {
        if ( _a.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_ACTION );
        query.addBindValue ( _a.task().toString() );
        query.addBindValue ( _a.project().toString() );
        query.addBindValue ( _a.collaborationType().toString() );
        query.addBindValue ( _a.name() );
        query.addBindValue ( _a.comment() );
        bindTimeValue ( query, _a.startTime() );
        bindTimeValue ( query, _a.endTime() );
        query.addBindValue ( _a.reviewed() );
        query.addBindValue ( _a.billed() );
        query.addBindValue ( _a.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success Action::assign_query_values_to_entity ( QSqlQuery &query, dp::Action &a ) const
      {
        QUuid const& task_id = query.value ( 0 ).toString();
        a.setTask ( task_id );
        QUuid const& project_id = query.value ( 1 ).toString();
        a.setProject ( project_id );
        QDateTime _start, _end;
        QUuid const& collaboration_id = query.value ( 2 ).toString();
        a.setCollaborationType(collaboration_id);
        a.setName ( query.value ( 3 ).toString() );
        a.setComment ( query.value ( 4 ).toString() );
        _start.setTime_t ( query.value ( 5 ).toUInt() );
        a.setStartTime ( _start );
        _end.setTime_t ( query.value ( 6 ).toUInt() );
        a.setEndTime ( _end );
        a.setReviewed ( query.value ( 7 ).toBool() );
        a.setBilled ( query.value ( 8 ).toBool() );
        return successful();
      }
      // ---------------------------------------------------------------------------------
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
