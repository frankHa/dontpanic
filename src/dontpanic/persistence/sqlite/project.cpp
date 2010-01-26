#include "persistence/sqlite/project.hpp"
#include "libdontpanic/project.hpp"
#include "persistence/execute_query.hpp"
//Qt includes
#include <QVariant>
//KDE includes
#include <KDebug>
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
      const QString INSERT_PROJECT =
        "INSERT INTO p_project(p_id, p_name, p_visible, p_creation_date)VALUES(?, ?, 1, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_PROJECTS =
        "SELECT p_id, p_name, p_creation_date FROM p_project WHERE (p_visible <> 0)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_PROJECT =
        "SELECT DISTINCT p_id, p_name, p_creation_date FROM p_project WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_PROJECT =
        "UPDATE p_project set(p_name=?, p_creation_date=?) WHERE (p_id=?)";
	// ---------------------------------------------------------------------------------
	const QString REMOVE_PROJECT = 
	"DELETE FROM p_project WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success Project::persist ( dp::Project const&_project ) const
      {
        if ( exists ( _project ) )
        {
          return update ( _project );
        }
        return insert ( _project );
      }
      // ---------------------------------------------------------------------------------
      success Project::remove(dp::Project const& _project) const
      {
	if ( _project.id().isNull())
        {
          return error();
        }
	if(!exists(_project))
	{
	    return successful();
	}
	QSqlQuery query;
	query.prepare(REMOVE_PROJECT);
	query.addBindValue(_project.id().toString());
	if(execute(query).has_failed())
	{
	  return error();
	}
	return successful();
      }
      // ---------------------------------------------------------------------------------
      success Project::load ( dp::Project &p ) const
      {
        kDebug()<<p.id().toString();
        if ( p.id().isNull())
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_PROJECT );
        query.addBindValue ( p.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          kWarning()<<"last error: "<<query.lastError();
          return error();
        }
        if ( !query.first() )
        {
          kWarning()<<"last error: "<<query.lastError();
          return error();
        }
        return assign_query_values_to_entity ( query, p );
      }
      // ---------------------------------------------------------------------------------
      success Project::findAll(dp::ProjectList &l) const
      {
	QSqlQuery query;
	query.prepare(SELECT_ALL_PROJECTS);
	if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
	  dp::Project _p(QUuid(query.value(0).toString()));
	  assign_query_values_to_entity(query, _p);
	  l.append(_p);
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool Project::exists ( const dp::Project& _project ) const
      {
        if ( _project.id().isNull() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_PROJECT );
        query.addBindValue ( _project.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success Project::insert ( dp::Project const& _p ) const
      {
        if ( _p.id().isNull())
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( INSERT_PROJECT );
        query.addBindValue ( _p.id().toString() );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.creationDate() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success Project::update ( const dp::Project& _p ) const
      {
        if ( _p.id().isNull())
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_PROJECT );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.creationDate() );
        query.addBindValue ( _p.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success Project::assign_query_values_to_entity ( QSqlQuery& query, dp::Project& p ) const
      {
        p.setName ( query.value ( 1 ).toString() );
        p.setCreationDate ( query.value ( 2 ).toDateTime() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
