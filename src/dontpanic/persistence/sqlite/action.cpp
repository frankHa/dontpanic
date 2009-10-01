#include <persistence/sqlite/action.hpp>
#include "persistence/execute_query.hpp"
#include <libdontpanic/action.hpp>

#include <persistence/sqlite/task.hpp>
#include <persistence/sqlite/project.hpp>
#include <QVariant>
#include <QSqlQuery>
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
      success Action::persist ( dp::Action &_a ) const
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
      Action_ptr Action::findActive() const
      {
        QSqlQuery query;
        query.prepare ( SELECT_ACTIVE );
        if ( execute ( query ).has_failed() )
        {
          qWarning() << "query SELECT_ACTIVE failed";
          return Action_ptr();
        }
        if ( !query.first() )
        {
          qWarning() << "no active action found";
          return Action_ptr();
        }
        QUuid const&id = query.value ( 0 ).toString();
        Action_ptr _a ( new dp::Action ( id ) );
        if ( load ( *_a ).has_failed() )
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
      success Action::insert ( dp::Action &_a ) const
      {
        {
          if ( _a.id().isNull() )
          {
            return error();
          }
          QSqlQuery query;
          query.prepare ( INSERT_ACTION );
          query.addBindValue ( _a.id().toString() );
          query.addBindValue ( _a.task()->id().toString() );
          query.addBindValue ( _a.project()->id().toString() );
          query.addBindValue ( _a.collaborationType()->id().toString() );
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
        query.addBindValue ( _a.task()->id().toString() );
        query.addBindValue ( _a.project()->id().toString() );
        query.addBindValue ( _a.collaborationType()->id().toString() );
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
        dp::Task::ptr _task ( new dp::Task ( task_id ) );
        task().load ( *_task );
        a.setTask ( _task );
        QUuid const& project_id = query.value ( 1 ).toString();
        dp::Project::ptr _project ( new dp::Project ( project_id ) );
        project().load ( *_project );
        a.setProject ( _project );
        QDateTime _start, _end;
        QUuid const& collaboration_id = query.value ( 2 ).toString();
        //TODO load collaboration type!!!
        dp::CollaborationType_ptr _ct(new CollaborationType(collaboration_id));
        a.setCollaborationType(_ct);
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
