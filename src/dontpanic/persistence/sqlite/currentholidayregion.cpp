#include "persistence/sqlite/currentholidayregion.hpp"
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
      const QString CREATE_TABLE_CURRENT_HOLIDAY_REGION =
        "CREATE TABLE IF NOT EXISTS chr_current_holiday_region \
      (chr_region TEXT PRIMARY KEY )";
      // ---------------------------------------------------------------------------------
      const QString INSERT_CURRENT_HOLIDAY_REGION =
        "INSERT INTO chr_current_holiday_region(chr_region)VALUES(?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_CURRENT_HOLIDAY_REGION =
        "SELECT DISTINCT chr_region FROM chr_current_holiday_region";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_CURRENT_HOLIDAY_REGION =
        "UPDATE chr_current_holiday_region set chr_region=?";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_CURRENT_HOLIDAY_REGION =
        "DELETE FROM chr_current_holiday_region";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::create_table() const
      {
        QSqlQuery query;
        query.prepare(CREATE_TABLE_CURRENT_HOLIDAY_REGION);
        return execute(query);
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::persist ( QString const&_region ) const
      {
        if ( exists () )
        {
          return update ( _region );
        }
        return insert ( _region );
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::load ( QString &_wt ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_CURRENT_HOLIDAY_REGION );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        if ( !query.first() )
        {
          return error();
        }
        return assign_query_values_to_entity ( query, _wt );
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::remove ( ) const
      {
        if ( !exists ( ) )
        {
          return successful();
        }
        QSqlQuery query;
        query.prepare ( REMOVE_CURRENT_HOLIDAY_REGION );
        //query.addBindValue ( _wt.day() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool CurrentHolidayRegion::exists ( ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_CURRENT_HOLIDAY_REGION );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::insert ( QString const& _wt ) const
      {
        QSqlQuery query;
        query.prepare ( INSERT_CURRENT_HOLIDAY_REGION );
        query.addBindValue ( _wt );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::update ( QString const& _wt ) const
      {
        QSqlQuery query;
        query.prepare ( UPDATE_CURRENT_HOLIDAY_REGION );
        query.addBindValue ( _wt );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success CurrentHolidayRegion::assign_query_values_to_entity ( QSqlQuery& query, QString& _wt ) const
      {
        _wt = ( query.value ( 0 ).toString() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
