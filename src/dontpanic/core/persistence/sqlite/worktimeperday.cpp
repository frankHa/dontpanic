#include "persistence/sqlite/worktimeperday.hpp"
#include "libdontpanic/worktimeperday.h"
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
      const QString CREATE_TABLE_WORK_TIME_PER_DAY =
      "CREATE TABLE IF NOT EXISTS w_work_time_per_day \
      (w_day int PRIMARY KEY, w_time int)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_WORKTIME =
        "INSERT INTO w_work_time_per_day(w_day, w_time)VALUES(?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_WORKTIMES =
        "SELECT w_day, w_time FROM w_work_time_per_day order by w_day";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_WORKTIME =
        "SELECT DISTINCT w_day, w_time FROM w_work_time_per_day WHERE (w_day=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_WORKTIME =
        "UPDATE w_work_time_per_day set w_time=? WHERE (w_day=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_WORKTIME =
        "DELETE FROM w_work_time_per_day WHERE (w_day=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::create_table() const
      {
        QSqlQuery query;
        query.prepare(CREATE_TABLE_WORK_TIME_PER_DAY);
        if(execute(query).was_successful())
        {
          insert_default_entries();
          return successful();          
        }
        return error();
        
      }
      // ---------------------------------------------------------------------------------
      void WorktimePerDay::insert_default_entries() const
      {
        QMap<Qt::DayOfWeek, QTime> map;
        map[Qt::Monday] = QTime ( 8, 0 );
        map[Qt::Tuesday] = QTime ( 8, 0 );
        map[Qt::Wednesday] = QTime ( 8, 0 );
        map[Qt::Thursday] = QTime ( 8, 0 );
        map[Qt::Friday] = QTime ( 8, 0 );
        map[Qt::Saturday] = QTime ( 0, 0 );
        map[Qt::Sunday] = QTime ( 0, 0 );
        QList<Qt::DayOfWeek> days = map.keys();
        foreach(Qt::DayOfWeek day, days)
        {
          dp::WorktimePerDay wtpd(day);
          if(!exists(wtpd))
          {
            wtpd.setPlannedWorkingHours(map[day]);
            persist(wtpd);
          }
        }
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::persist ( dp::WorktimePerDay const&_wt ) const
      {
        if ( exists ( _wt ) )
        {
          return update ( _wt );
        }
        return insert ( _wt );
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::load ( dp::WorktimePerDay &_wt ) const
      {
        if ( !_wt.isValid() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_WORKTIME );
        query.addBindValue ( _wt.day() );
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
      success WorktimePerDay::remove ( dp::WorktimePerDay const& _wt ) const
      {
        if ( _wt.day() == 0 )
        {
          return error();
        }
        if ( !exists ( _wt ) )
        {
          return successful();
        }
        QSqlQuery query;
        query.prepare ( REMOVE_WORKTIME );
        query.addBindValue ( _wt.day() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::findAll ( dp::WorktimePerDayList &l ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_ALL_WORKTIMES );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
          dp::WorktimePerDay _t ( ( Qt::DayOfWeek ) query.value ( 0 ).toInt() );
          assign_query_values_to_entity ( query, _t );
          l.append ( _t );
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      bool WorktimePerDay::exists ( const dp::WorktimePerDay& _wt ) const
      {
        if ( !_wt.isValid() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_WORKTIME );
        query.addBindValue ( _wt.day() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::insert ( dp::WorktimePerDay const& _wt ) const
      {
        QSqlQuery query;
        query.prepare ( INSERT_WORKTIME );
        query.addBindValue ( _wt.day() );
        query.addBindValue ( _wt.plannedWorkingHours() );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::update ( const dp::WorktimePerDay& _wt ) const
      {
        if ( !_wt.isValid() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_WORKTIME );
        query.addBindValue ( _wt.plannedWorkingHours() );
        query.addBindValue ( _wt.day() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success WorktimePerDay::assign_query_values_to_entity ( QSqlQuery& query, dp::WorktimePerDay& _wt ) const
      {
        _wt.setPlannedWorkingHours ( query.value ( 1 ).toTime() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
