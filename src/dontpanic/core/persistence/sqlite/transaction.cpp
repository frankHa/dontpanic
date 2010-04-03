/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "transaction.h"
#include <persistence/execute_query.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace  _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      Transaction::Transaction()
          : _M_open ( false )
      {
        begin();
      }
      // ---------------------------------------------------------------------------------
      Transaction::~Transaction()
      {
        if ( !isOpen() )
        {
          return;
        }
        rollback();
      }
      // ---------------------------------------------------------------------------------
      success Transaction::commit()
      {
        QSqlQuery query ( "COMMIT" );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          _M_open = false;
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success Transaction::rollback()
      {
        QSqlQuery query ( "ROLLBACK" );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          _M_open = false;
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      bool Transaction::isOpen() const
      {
        return _M_open;
      }
      // ---------------------------------------------------------------------------------
      success Transaction::begin()
      {
        QSqlQuery query("BEGIN TRANSACTION");
        success result = execute(query);
        if(result.was_successful())
        {
          _M_open = true;
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
    }
  }
}

