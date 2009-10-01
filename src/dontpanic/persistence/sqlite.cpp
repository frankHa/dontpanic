#include "persistence/sqlite.hpp"
#include "persistence/execute_query.hpp"
#include "persistence/sqlite/project.hpp"
#include "persistence/sqlite/action.hpp"
#include "persistence/sqlite/task.hpp"
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
    //sqlite_private declaration:
    // ---------------------------------------------------------------------------------
    class Sqlite::sqlite_private
    {
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        sqlite_private ( Sqlite *self ) : _M_self ( self ) {}
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        success open_database_connection() const;
        // ---------------------------------------------------------------------------------
        success update_database_schema_if_necessary() const;
        // ---------------------------------------------------------------------------------
        success persist ( Project &_project ) const;
        // ---------------------------------------------------------------------------------
        success persist ( Task &_task ) const;
        // ---------------------------------------------------------------------------------
        success persist ( Action &_action ) const;
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QString storage_dir() const;
        // ---------------------------------------------------------------------------------
        success prepare_storage_directory() const;
        // ---------------------------------------------------------------------------------
        QString database_name() const;
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        Sqlite *_M_self;
        // ---------------------------------------------------------------------------------

    };//sqlite_private
    // ---------------------------------------------------------------------------------
    //Sqlite impl:
    // ---------------------------------------------------------------------------------
    Sqlite::Sqlite()
        : d ( new sqlite_private ( this ) ) {}
    // ---------------------------------------------------------------------------------
    success Sqlite::open_database_connection()
    {
      return d->open_database_connection();
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::update_database_schema_if_necessary()
    {
      return d->update_database_schema_if_necessary();
    }

    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Project& _project )
    {
      return d->persist ( _project );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Task& _t )
    {
      return d->persist ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::persist ( Action& _a )
    {
      return d->persist ( _a );
    }
    // ---------------------------------------------------------------------------------
    // sqlite_private impl:
    // ---------------------------------------------------------------------------------
    success Sqlite::sqlite_private::open_database_connection() const
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
    dp::success Sqlite::sqlite_private::update_database_schema_if_necessary() const
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
      if ( !query.exec ( CREATE_TABLE_ACTION ) )
      {
        qDebug() << query.lastError();
        return error();
      }
      return successful();
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::sqlite_private::persist ( Project& _project ) const
    {
      return _sqlite::project().persist ( _project );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::sqlite_private::persist ( Task& _t ) const
    {
      return _sqlite::task().persist ( _t );
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::sqlite_private::persist ( Action& _a ) const
    {
      return _sqlite::action().persist ( _a );
    }
    // ---------------------------------------------------------------------------------
    QString Sqlite::sqlite_private::storage_dir() const
    {
      return QDir::homePath() + "/.dontpanic/";
    }
    // ---------------------------------------------------------------------------------
    success Sqlite::sqlite_private::prepare_storage_directory() const
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
    QString Sqlite::sqlite_private::database_name() const
    {
      return storage_dir() + DB_FILE_NAME;
    }
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
