#include "persistence/sqlite/reporttype.hpp"
#include "libdontpanic/reporttype.h"
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
      const QString CREATE_TABLE_REPORT_TYPE =
        "CREATE TABLE IF NOT EXISTS p_project \
      (p_id TEXT PRIMARY KEY, p_name TEXT, p_visible INTEGER, p_creation_date TEXT, p_comment TEXT)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_REPORT_TYPE =
        "INSERT INTO p_project(p_id, p_name, p_visible, p_creation_date, p_comment)VALUES(?, ?, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_REPORT_TYPES =
        "SELECT p_id, p_name, p_visible, p_creation_date, p_comment FROM p_project order by p_name";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_REPORT_TYPE =
        "SELECT DISTINCT p_id, p_name, p_visible, p_creation_date, p_comment FROM p_project WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_REPORT_TYPE =
        "UPDATE p_project set p_name=?, p_visible=?, p_creation_date=?, p_comment=? WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_REPORT_TYPE =
        "DELETE FROM p_project WHERE (p_id=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success _sqlite::ReportType::create_table()
      {
        QSqlQuery query;
        query.prepare ( CREATE_TABLE_REPORT_TYPE );
        return execute(query);
      }
      // ---------------------------------------------------------------------------------
      success ReportType::persist ( dp::ReportType const&_project ) const
      {
        if ( exists ( _project ) )
        {
          return update ( _project );
        }
        return insert ( _project );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::remove ( dp::ReportType const& _project ) const
      {
        if ( _project.id().isNull() )
        {
          return error();
        }
        if ( !exists ( _project ) )
        {
          return successful();
        }
        QSqlQuery query;
        query.prepare ( REMOVE_REPORT_TYPE );
        query.addBindValue ( _project.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success ReportType::load ( dp::ReportType &p ) const
      {
        if ( p.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_REPORT_TYPE );
        query.addBindValue ( p.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          kWarning() << "last error: " << query.lastError();
          return error();
        }
        if ( !query.first() )
        {
          kWarning() << "last error: " << query.lastError();
          return error();
        }
        return assign_query_values_to_entity ( query, p );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::findAll ( dp::ReportTypeList &l ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_ALL_REPORT_TYPES );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
          dp::ReportType _p ( Uuid ( query.value ( 0 ).toString() ) );
          assign_query_values_to_entity ( query, _p );
          l.append ( _p );
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool ReportType::exists ( const dp::ReportType& _project ) const
      {
        if ( _project.id().isNull() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_REPORT_TYPE );
        query.addBindValue ( _project.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success ReportType::insert ( dp::ReportType const& _p ) const
      {
        if ( _p.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( INSERT_REPORT_TYPE );
        query.addBindValue ( _p.id().toString() );
        query.addBindValue ( _p.title() );
        //query.addBindValue ( _p.isVisible() );
        //query.addBindValue ( _p.creationDate() );
        //query.addBindValue ( _p.comment() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success ReportType::update ( const dp::ReportType& _p ) const
      {
        if ( _p.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_REPORT_TYPE );
        query.addBindValue ( _p.title() );
        //query.addBindValue ( _p.isVisible() );
        //query.addBindValue ( _p.creationDate() );
        //query.addBindValue ( _p.comment() );
        query.addBindValue ( _p.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::assign_query_values_to_entity ( QSqlQuery& query, dp::ReportType& p ) const
      {
        p.setTitle ( query.value ( 1 ).toString() );
        //p.setVisible ( query.value ( 2 ).toBool() );
        //p.setCreationDate ( query.value ( 3 ).toDateTime() );
        //p.setComment ( query.value ( 4 ).toString() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
