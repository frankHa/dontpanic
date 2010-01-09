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
        "INSERT INTO t_task(t_id, t_name, t_visible, t_solo_effort, t_chargeable, t_creation_date)VALUES(?, ?, 1, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_TASKS =
        "SELECT t_id, t_name, t_solo_effort, t_chargeable, t_creation_date FROM t_task WHERE (t_visible <> 0)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_TASK =
        "SELECT DISTINCT t_name, t_solo_effort, t_chargeable, t_creation_date FROM t_task WHERE (t_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_TASK =
        "UPDATE p_project set t_name=?, t_solo_effort=?, t_chargeable=?, t_creation_date=? WHERE (t_id=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_TASK = 
	"UPDATE t_task set(t_visible=0) WHERE (t_id=?)";
	// ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success Task::persist ( dp::Task const&_task ) const
      {
        if ( exists ( _task ) )
        {
          return update ( _task );
        }
        return insert ( _task );
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
      success Task::remove(dp::Task const& _task) const
      {
	if ( _task.id().isNull())
        {
          return error();
        }
	if(!exists(_task))
	{
	    return successful();
	}
	QSqlQuery query;
	query.prepare(REMOVE_TASK);
	query.addBindValue(_task.id().toString());
	if(execute(query).has_failed())
	{
	  return error();
	}
	return successful();
      }
      // ---------------------------------------------------------------------------------
      success Task::findAll(dp::TaskList &l) const
      {
	QSqlQuery query;
	query.prepare(SELECT_ALL_TASKS);
	if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
	  dp::Task _t(QUuid(query.value(0).toString()));
	  assign_query_values_to_entity(query, _t);
	  l.append(_t);
        }
        return successful();
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
      success Task::insert ( dp::Task const& _t ) const
      {
        QSqlQuery query;
        query.prepare ( INSERT_TASK );
        query.addBindValue ( _t.id().toString() );
        query.addBindValue ( _t.name() );
        query.addBindValue ( _t.isSoloEffort() );
        query.addBindValue ( _t.isChargeable() );
        query.addBindValue ( _t.creationDate() );
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
        query.addBindValue ( _t.isSoloEffort() );
        query.addBindValue ( _t.isChargeable() );
        query.addBindValue ( _t.creationDate() );
        query.addBindValue ( _t.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success Task::assign_query_values_to_entity ( QSqlQuery& query, dp::Task& t ) const
      {
        t.setName ( query.value ( 1 ).toString() );
        t.setIsSoloEffort ( query.value ( 2 ).toBool() );
        t.setIsChargeable ( query.value ( 3 ).toBool() );
        t.setCreationDate ( query.value ( 4 ).toDateTime() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
