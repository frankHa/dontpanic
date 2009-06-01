#ifndef DP_PERSISTANCE_EXECUTE_HPP
#define DP_PERSISTANCE_EXECUTE_HPP
//dp includes
#include "defines.hpp"
#include "libdontpanic/success.hpp"
//Qt includes
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  namespace persistance
  {
    // ---------------------------------------------------------------------------------
    inline success execute ( QSqlQuery &query )
    {
      if ( !query.exec() )
      {
        qDebug() << query.lastError();
        return error();
      }
      return successful();
    }
    // ---------------------------------------------------------------------------------
  }//persistance
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_PERSISTANCE_EXECUTE_HPP
