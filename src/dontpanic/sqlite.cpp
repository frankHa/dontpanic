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
    QString home_dir()
    {
      return QDir::homePath() + "/.dontpanic/";
    }
    // ---------------------------------------------------------------------------------
    success prepare_home_directory()
    {
      QDir _dir ( home_dir() );
      if ( _dir.exists() )
      {
        return successful();
      }
      if ( _dir.mkpath ( home_dir() ) )
      {
        return successful();
      }
      return error();
    }
    // ---------------------------------------------------------------------------------
    QString database_name()
    {
      return home_dir() + DB_FILE_NAME;
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
  success Sqlite::open_database_connection()
  {
    if ( detail::prepare_home_directory().has_failed() )
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
