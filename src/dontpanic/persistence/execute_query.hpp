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
  namespace _persistence
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
    template<typename time_type>
    void bindTimeValue ( QSqlQuery &query, time_type const& _t )
    {
      if ( _t.isValid() )

      {
        query.addBindValue ( _t.toTime_t() );
      }
      else
      {
        query.addBindValue ( QVariant("NULL") );
      }
    }
    // ---------------------------------------------------------------------------------
  }//_persistance
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_PERSISTANCE_EXECUTE_HPP
