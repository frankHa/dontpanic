#include "sqlite.hpp"
#include "libdontpanic/project.hpp"
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
// inserting table rows:
// ---------------------------------------------------------------------------------
#define INSERT_PROJECT \
  "INSERT INTO p_project(p_name, p_visible, p_creation_date)VALUES(?, ?, ?)"

#define SELECT_PROJECT \
  "SELECT DISTINCT p_name, p_visible, p_creation_date FROM p_project WHERE (p_id=?)"

#define UPDATE_PROJECT \
  "UPDATE p_project set(p_name=?, p_visible=?, p_creation_date=?) WHERE (p_id=?)"
// ---------------------------------------------------------------------------------
namespace dp
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
      success persist ( project &_project ) const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      bool exists ( project const& _project ) const;
      // ---------------------------------------------------------------------------------
      success insert ( project &_p ) const;
      // ---------------------------------------------------------------------------------
      success update ( project const& _p )const;
      // ---------------------------------------------------------------------------------
      QString storage_dir()const;
      // ---------------------------------------------------------------------------------
      success prepare_storage_directory()const;
      // ---------------------------------------------------------------------------------
      QString database_name()const;
      // ---------------------------------------------------------------------------------
      success execute ( QSqlQuery &query )const;
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
  success Sqlite::persist ( project& _project )
  {
    return d->persist ( _project );
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
  success Sqlite::sqlite_private::persist ( project& _project ) const
  {
    //TODO: add support for updating existing entities:
    //TODO: update id on referenced C++ object after an insertion
    if ( exists ( _project ) )
    {
      return update ( _project );
    }
    return insert ( _project );

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
  bool Sqlite::sqlite_private::exists ( const dp::project& _project ) const
  {
    if ( _project.id() == 0 )
    {
      return false;
    }
    QSqlQuery query;
    query.prepare ( SELECT_PROJECT );
    query.addBindValue ( _project.id() );
    if( execute ( query ).has_failed())
    {
      return false;
    }
    return query.first();
  }
  // ---------------------------------------------------------------------------------
  success Sqlite::sqlite_private::insert ( project& _p ) const
  {
    QSqlQuery query;
    query.prepare ( INSERT_PROJECT );
    query.addBindValue ( _p.name() );
    query.addBindValue ( _p.is_visible() );
    query.addBindValue ( _p.creation_date() );
    if( execute ( query ).has_failed())
    {
      return error();
    }
    _p.set_id(query.lastInsertId().toULongLong());
    return successful();
  }
  // ---------------------------------------------------------------------------------
  success Sqlite::sqlite_private::update ( const dp::project& _p ) const
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
  success Sqlite::sqlite_private::execute ( QSqlQuery& query ) const
  {
    if ( !query.exec() )
    {
      qDebug() << query.lastError();
      return error();
    }
    return successful();
  }

  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
