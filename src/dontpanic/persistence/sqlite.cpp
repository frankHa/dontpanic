#include "persistence/sqlite.hpp"
#include "persistence/execute_query.hpp"
#include "persistence/sqlite/project.hpp"
#include "persistence/sqlite/currentholidayregion.hpp"
#include "persistence/sqlite/action.hpp"
#include "persistence/sqlite/task.hpp"
#include "persistence/sqlite/reporttype.hpp"
#include "persistence/sqlite/actiontemplate.hpp"
#include "persistence/sqlite/worktimeperday.hpp"
#include "libdontpanic/project.hpp"
#include "libdontpanic/task.hpp"
//Qt includes
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
// ---------------------------------------------------------------------------------

#define DB_FILE_NAME  "dontpanic.sqlite"
#define CURRENT_SCHEMA_VERSION "1.0"

//some SQL statements:
// ---------------------------------------------------------------------------------
// creating tables:
// ---------------------------------------------------------------------------------
// #define CREATE_TABLE_LEAVE_TYPE\
//   "CREATE TABLE IF NOT EXISTS lt_leave_type \
// (lt_id INTEGER PRIMARY KEY, lt_name TEXT, lt_paid INTEGER, lt_description TEXT)"
// 
// #define CREATE_TABLE_COLLABORATION_TYPE\
//   "CREATE TABLE IF NOT EXISTS ct_collaboration_type \
// (ct_id TEXT PRIMARY KEY, ct_name TEXT, ct_visible INTEGER,\
// ct_creation_date TEXT, ct_solo_effort INTEGER, ct_interrupting INTEGER)"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    QString storage_dir()
    {
      return QDir::homePath() + "/.dontpanic/";
    }
    // ---------------------------------------------------------------------------------
    success prepare_storage_directory()
    {
      QDir _dir ( storage_dir() );
      if ( _dir.exists() )
      {
        return successful();
      }
      if ( _dir.mkpath ( storage_dir() ) )
      {
        return successful();
      }
      return error();
    }
    // ---------------------------------------------------------------------------------
    QString database_name()
    {
      return storage_dir() + DB_FILE_NAME;
    }
    // ---------------------------------------------------------------------------------
    //Sqlite impl:
    // ---------------------------------------------------------------------------------
    Sqlite::Sqlite(){}
    // ---------------------------------------------------------------------------------
    success Sqlite::open_database_connection() const
    {
      if ( prepare_storage_directory().has_failed() )
      {
        return error();
      }
      QSqlDatabase db = QSqlDatabase::addDatabase ( "QSQLITE" );
      db.setDatabaseName ( database_name() );
      if ( db.open() )
      {
        return successful();
      }
      return error();
    }
    // ---------------------------------------------------------------------------------
    dp::success Sqlite::update_database_schema_if_necessary() const
    {
      QSqlQuery query;
      if(_sqlite::project().create_table().has_failed())
      {
        return error();
      }
      if(_sqlite::task().create_table().has_failed())
      {
        return error();
      }
//       if ( !query.exec ( CREATE_TABLE_LEAVE_TYPE ) )
//       {
//         qDebug() << query.lastError();
//         return error();
//       }
//       if ( !query.exec ( CREATE_TABLE_COLLABORATION_TYPE ) )
//       {
//         qDebug() << query.lastError();
//         return error();
//       }
      if(_sqlite::actionTemplate().create_table().has_failed())
      {
        return error();
      }
      if(_sqlite::action().create_table().has_failed())
      {
        return error();
      }
      if(_sqlite::worktime_per_day().create_table().has_failed())
      {
        return error();
      }
      if(_sqlite::current_holiday_region().create_table().has_failed())
      {
        return error();
      }
      return successful();
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( WorktimePerDay const& _wt ) const
    {
      return _sqlite::worktime_per_day().persist ( _wt );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( WorktimePerDay const& _wt ) const
    {
      return _sqlite::worktime_per_day().remove ( _wt );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::load ( WorktimePerDay & _wt ) const
    {
      return _sqlite::worktime_per_day().load ( _wt );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(WorktimePerDayList & _wl) const
    {
      return _sqlite::worktime_per_day().findAll(_wl);
    }
    
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Project const& _project ) const
    {
      return _sqlite::project().persist ( _project );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( Project const& _project ) const
    {
      return _sqlite::project().remove ( _project );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::load ( Project & _project ) const
    {
      return _sqlite::project().load ( _project );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(ProjectList & _pl) const
    {
      return _sqlite::project().findAll(_pl);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Task const& _t ) const
    {
      return _sqlite::task().persist ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::load ( Task & _t ) const
    {
      return _sqlite::task().load ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( Task const& _t ) const
    {
      return _sqlite::task().remove ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(TaskList & _tl) const
    {
      return _sqlite::task().findAll(_tl);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( ActionTemplate const& _t ) const
    {
      return _sqlite::actionTemplate().persist ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::load ( ActionTemplate & _t ) const
    {
      return _sqlite::actionTemplate().load ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( ActionTemplate const& _t ) const
    {
      return _sqlite::actionTemplate().remove ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(TemplateList & _tl) const
    {
      return _sqlite::actionTemplate().findAll(_tl);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Action const& _a ) const
    {
      return _sqlite::action().persist ( _a );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( Action const& _t ) const
    {
      return _sqlite::action().remove ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(ActionList & _tl, QDateTime const& from, QDateTime const& to) const
    {
      return _sqlite::action().findAll(_tl, from, to);
    }
    // ---------------------------------------------------------------------------------
    Action Sqlite::lastAction() const
    {
      return _sqlite::action().findLastAction();
    }
    // ---------------------------------------------------------------------------------
    bool Sqlite::hasActionsFor(QDate const& date)const
    {
      return _sqlite::action().hasActionFor(date);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persistCurrentHolidayRegion(QString const& region) const
    {
      return _sqlite::current_holiday_region().persist(region);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::removeCurrentHolidayRegion() const
    {
      return _sqlite::current_holiday_region().remove();
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::loadCurrentHolidayRegion(QString & region) const
    {
      return _sqlite::current_holiday_region().load(region);
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( ReportType const& _t ) const
    {
      return _sqlite::report_type().persist ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::load ( ReportType & _t ) const
    {
      return _sqlite::report_type().load ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::remove ( ReportType const& _t ) const
    {
      return _sqlite::report_type().remove ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::findAll(ReportTypeList & _tl) const
    {
      return _sqlite::report_type().findAll(_tl);
    }
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
