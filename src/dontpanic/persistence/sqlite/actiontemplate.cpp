#include <persistence/sqlite/actiontemplate.hpp>
#include "persistence/execute_query.hpp"
#include <libdontpanic/actiontemplate.hpp>

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
      const QString INSERT_ACTION_TEMPLATE =
        "INSERT INTO at_action_template(at_id, at_t_task , at_p_project,at_ct_collaboration_type,\
        at_name, at_comment, at_icon)VALUES(?, ?, ?, ?, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_ACTION_TEMPLATE = 
      "DELETE FROM at_action_template WHERE (at_id=?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_ACTION_TEMPLATES =
        "SELECT at_id, at_t_task , at_p_project,at_ct_collaboration_type,\
        at_name, at_comment, at_icon FROM at_action_template";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_ACTION_TEMPLATE =
        "SELECT DISTINCT at_id, at_t_task , at_p_project,at_ct_collaboration_type,\
        at_name, at_comment, at_icon FROM at_action_template WHERE (at_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_ACTION_TEMPLATE =
        "UPDATE at_action_template set at_t_task=?, at_p_project=?,at_ct_collaboration_type=?,\
        at_name=?, at_comment=?, at_icon=? WHERE (at_id=?)";
      // ---------------------------------------------------------------------------------
      success ActionTemplate::persist ( dp::ActionTemplate const&_a ) const
      {
        if ( exists ( _a ) )
        {
          return update ( _a );
        }
        return insert ( _a );
      }
      // ---------------------------------------------------------------------------------
      success ActionTemplate::load ( dp::ActionTemplate &a ) const
      {
        if ( a.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_ACTION_TEMPLATE );
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
      success ActionTemplate::remove(dp::ActionTemplate const& _a) const
      {
        kDebug()<<_a.id().toString();
        if ( !_a.isValid())
        {
          return error();
        }
        if(!exists(_a))
        {
          return successful();
        }
        QSqlQuery query;
        query.prepare(REMOVE_ACTION_TEMPLATE);
        query.addBindValue(_a.id().toString());
        if(execute(query).has_failed())
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success ActionTemplate::findAll(dp::TemplateList &l) const
      {
        QSqlQuery query;
        query.prepare(SELECT_ALL_ACTION_TEMPLATES);
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
          dp::ActionTemplate _p(Uuid(query.value(0).toString()));
          assign_query_values_to_entity(query, _p);
          l.append(_p);
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      //private stuff:
      // ---------------------------------------------------------------------------------
      bool ActionTemplate::exists ( dp::ActionTemplate const& _a ) const
      {
        if ( !_a.isValid() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_ACTION_TEMPLATE );
        query.addBindValue ( _a.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success ActionTemplate::insert ( dp::ActionTemplate const&_a ) const
      {
        {
          if ( _a.id().isNull() )
          {
            return error();
          }
          QSqlQuery query;
          query.prepare ( INSERT_ACTION_TEMPLATE );
          query.addBindValue ( _a.id().toString() );
          query.addBindValue ( _a.task().toString() );
          query.addBindValue ( _a.project().toString() );
          query.addBindValue ( _a.collaborationType().toString() );
          query.addBindValue ( _a.name() );
          query.addBindValue ( _a.comment() );
          query.addBindValue ( _a.icon() );
          if ( execute ( query ).has_failed() )
          {
            return error();
          }
          return successful();
        }
      }
      // ---------------------------------------------------------------------------------
      success ActionTemplate::update ( dp::ActionTemplate const& _a ) const
      {
        if ( _a.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_ACTION_TEMPLATE );
        query.addBindValue ( _a.task().toString() );
        query.addBindValue ( _a.project().toString() );
        query.addBindValue ( _a.collaborationType().toString() );
        query.addBindValue ( _a.name() );
        query.addBindValue ( _a.comment() );
        query.addBindValue ( _a.icon() );
        query.addBindValue ( _a.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success ActionTemplate::assign_query_values_to_entity ( QSqlQuery &query, dp::ActionTemplate &a ) const
      {
        //QUuid const& id = query.value ( 0 ).toString();
        Uuid const& task_id = query.value ( 1 ).toString();
        a.setTask ( task_id );
        Uuid const& project_id = query.value ( 2 ).toString();
        a.setProject ( project_id );
        Uuid const& collaboration_id = query.value ( 3 ).toString();
        a.setCollaborationType(collaboration_id);
        a.setName ( query.value ( 4 ).toString() );
        a.setComment ( query.value ( 5 ).toString() );
        a.setIcon ( query.value ( 6 ).toString() );
        return successful();
      }
      // ---------------------------------------------------------------------------------
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
