#include "sqlite.hpp"
//Qt includes
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
// ---------------------------------------------------------------------------------

#define DB_FILE_NAME  "dontpanic.sqlite"
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
}//dp
// ---------------------------------------------------------------------------------
