#include "sqlite.hpp"
//Qt includes
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
// ---------------------------------------------------------------------------------

#define DB_FILE_NAME  "dontpanic.sqlite"
#define CURRENT_SCHEMA_VERSION "1.0"

//some SQL statements:
#define CREATE_TABLE_PROJECT\
  "CREATE TABLE IF NOT EXISTS p_project \
(p_id INTEGER PRIMARY KEY, p_name TEXT, p_visible INTEGER, p_creation_date TEXT)"

#define CREATE_TABLE_TASK\
  "CREATE TABLE IF NOT EXISTS t_task \
(t_id INTEGER PRIMARY KEY, t_name TEXT, t_visible INTEGER, \
t_solo_effort INTEGER, t_chargeable INTEGER, t_creation_date TEXT)"

#define CREATE_TABLE_LEAVE_TYPE\
  "CREATE TABLE IF NOT EXISTS lt_leave_type \
(lt_id INTEGER PRIMARY KEY, lt_name TEXT, lt_paid INTEGER, lt_description TEXT)"

#define CREATE_TABLE_COLLABORATION_TYPE\
  "CREATE TABLE IF NOT EXISTS ct_collaboration_type \
(ct_id INTEGER PRIMARY KEY, ct_name TEXT, ct_visible INTEGER,\
ct_creation_date TEXT, ct_solo_effort INTEGER, ct_interrupting INTEGER)"

#define CREATE_TABLE_ACTION\
  "CREATE TABLE IF NOT EXISTS a_action \
(a_id INTEGER PRIMARY KEY, a_t_task INTEGER references t_task(t_id) , a_project INTEGER references p_project(p_id),\
a_ct_collaboration_type INTEGER references ct_collaboration_type(ct_id),\
a_name TEXT, a_comment TEXT, a_start TEXT, a_end TEXT, a_reviewed INTEGER, a_billed INTEGER )"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace detail
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
  }
  // ---------------------------------------------------------------------------------
  success Sqlite::open_database_connection()
  {
    if ( detail::prepare_storage_directory().has_failed() )
    {
      return error();
    }
    QSqlDatabase db = QSqlDatabase::addDatabase ( "QSQLITE" );
    db.setDatabaseName ( detail::database_name() );
    if ( db.open() )
    {
      return successful();
    }
    return error();
  }
  // ---------------------------------------------------------------------------------
  dp::success Sqlite::update_database_schema_if_necessary()
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
}//dp
// ---------------------------------------------------------------------------------
