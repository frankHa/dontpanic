#include "persistence/sqlite/Project.hpp"
#include "libdontpanic/Project.hpp"
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
      const QString INSERT_PROJECT =
        "INSERT INTO p_project(p_name, p_visible, p_creation_date)VALUES(?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_PROJECTS =
        "SELECT p_id, p_name, p_visible, p_creation_date FROM p_project";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_VISIBLE_PROJECTS =
        SELECT_ALL_PROJECTS + " WHERE (p_visible <> 0)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_PROJECT =
        "SELECT DISTINCT p_id, p_name, p_visible, p_creation_date FROM p_project WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_PROJECT =
        "UPDATE p_project set(p_name=?, p_visible=?, p_creation_date=?) WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success Project::persist ( dp::Project &_project ) const
      {
        if ( exists ( _project ) )
        {
          return update ( _project );
        }
        return insert ( _project );
      }
      // ---------------------------------------------------------------------------------
      success Project::load ( dp::Project &p ) const
      {
        if ( p.id() == 0 )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_PROJECT );
        query.addBindValue ( p.id() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        if ( !query.first() )
        {
          return error();
        }
        return assign_query_values_to_entity ( query, p );
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool Project::exists ( const dp::Project& _project ) const
      {
        if ( _project.id() == 0 )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_PROJECT );
        query.addBindValue ( _project.id() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success Project::insert ( dp::Project& _p ) const
      {
        QSqlQuery query;
        query.prepare ( INSERT_PROJECT );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.isVisible() );
        query.addBindValue ( _p.creationDate() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        _p.setId ( query.lastInsertId().toULongLong() );
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success Project::update ( const dp::Project& _p ) const
      {
        QSqlQuery query;
        query.prepare ( UPDATE_PROJECT );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.isVisible() );
        query.addBindValue ( _p.creationDate() );
        query.addBindValue ( _p.id() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success Project::assign_query_values_to_entity ( QSqlQuery& query, dp::Project& p ) const
      {
        p.setId ( query.value ( 0 ).toULongLong() );
        p.setName ( query.value ( 1 ).toString() );
        p.setIsVisible ( query.value ( 2 ).toBool() );
        p.setCreationDate ( query.value ( 3 ).toDateTime() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
