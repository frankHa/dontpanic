#include "persistance/sqlite/Project.hpp"
#include "libdontpanic/Project.hpp"
#include "persistance/execute_query.hpp"
//Qt includes
#include <QVariant>
// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
// inserting table rows:
// ---------------------------------------------------------------------------------
#define INSERT_PROJECT \
  "INSERT INTO p_project(p_name, p_visible, p_creation_date)VALUES(?, ?, ?)"

#define SELECT_PROJECT \
  "SELECT DISTINCT p_name, p_visible, p_creation_date FROM p_project WHERE (p_id=?)"

#define UPDATE_PROJECT \
  "UPDATE p_project set(p_name=?, p_visible=?, p_creation_date=?) WHERE (p_id=?)"
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace persistance
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
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
        return successful();
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
        query.prepare ( SELECT_PROJECT );
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
        query.addBindValue ( _p.is_visible() );
        query.addBindValue ( _p.creation_date() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        _p.set_id ( query.lastInsertId().toULongLong() );
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success Project::update ( const dp::Project& _p ) const
      {
        QSqlQuery query;
        query.prepare ( UPDATE_PROJECT );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.is_visible() );
        query.addBindValue ( _p.creation_date() );
        query.addBindValue ( _p.id() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
