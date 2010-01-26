#include "persistence/sqlite.hpp"
#include "persistence/execute_query.hpp"
#include "persistence/sqlite/project.hpp"
#include "persistence/sqlite/action.hpp"
#include "persistence/sqlite/task.hpp"
#include "persistence/sqlite/actiontemplate.hpp"
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
#define CREATE_TABLE_PROJECT\
  "CREATE TABLE IF NOT EXISTS p_project \
(p_id TEXT PRIMARY KEY, p_name TEXT, p_visible INTEGER, p_creation_date TEXT)"

#define CREATE_TABLE_TASK\
  "CREATE TABLE IF NOT EXISTS t_task \
(t_id TEXT PRIMARY KEY, t_name TEXT, t_visible INTEGER, \
t_solo_effort INTEGER, t_chargeable INTEGER, t_creation_date TEXT)"

#define CREATE_TABLE_LEAVE_TYPE\
  "CREATE TABLE IF NOT EXISTS lt_leave_type \
(lt_id INTEGER PRIMARY KEY, lt_name TEXT, lt_paid INTEGER, lt_description TEXT)"

#define CREATE_TABLE_COLLABORATION_TYPE\
  "CREATE TABLE IF NOT EXISTS ct_collaboration_type \
(ct_id TEXT PRIMARY KEY, ct_name TEXT, ct_visible INTEGER,\
ct_creation_date TEXT, ct_solo_effort INTEGER, ct_interrupting INTEGER)"

#define CREATE_TABLE_ACTION_TEMPLATE\
  "CREATE TABLE IF NOT EXISTS at_action_template \
(at_id TEXT PRIMARY KEY, at_t_task TEXT references t_task(t_id) , at_p_project INTEGER references p_project(p_id),\
at_ct_collaboration_type TEXT references ct_collaboration_type(ct_id),\
at_name TEXT, at_comment TEXT, at_icon TEXT)"

#define CREATE_TABLE_ACTION\
  "CREATE TABLE IF NOT EXISTS a_action \
(a_id TEXT PRIMARY KEY, a_t_task TEXT references t_task(t_id) , a_p_project INTEGER references p_project(p_id),\
a_ct_collaboration_type TEXT references ct_collaboration_type(ct_id),\
a_name TEXT, a_comment TEXT, a_start INTEGER, a_end INTEGER, a_reviewed INTEGER, a_billed INTEGER )"
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
      if ( !query.exec ( CREATE_TABLE_PROJECT ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      if ( !query.exec ( CREATE_TABLE_TASK ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      if ( !query.exec ( CREATE_TABLE_LEAVE_TYPE ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      if ( !query.exec ( CREATE_TABLE_COLLABORATION_TYPE ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      if ( !query.exec ( CREATE_TABLE_ACTION_TEMPLATE ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      if ( !query.exec ( CREATE_TABLE_ACTION ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      return successful();
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
    success Sqlite::findAll(ActionList & _tl, QDateTime const& from, QDateTime const& to) const
    {
      return _sqlite::action().findAll(_tl, from, to);
    }
    // ---------------------------------------------------------------------------------
    Action Sqlite::activeAction() const
    {
      return _sqlite::action().findActive();
    }
    // ---------------------------------------------------------------------------------
    
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
