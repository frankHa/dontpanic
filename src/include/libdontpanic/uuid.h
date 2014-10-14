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

#ifndef DP_UUID_H
#define DP_UUID_H
#include <libdontpanic/defines.hpp>
#include <QUuid>
// ---------------------------------------------------------------------------------
namespace dp
{
  class Uuid;
}
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Uuid )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT Uuid
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      static Uuid generate();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Uuid();
      // ---------------------------------------------------------------------------------
      Uuid ( QUuid const& id );
      // ---------------------------------------------------------------------------------
      Uuid ( QString const& id );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool isNull() const;
      // ---------------------------------------------------------------------------------
      QString toString() const;
      // ---------------------------------------------------------------------------------
      bool operator!= ( Uuid const& rhs ) const;
      // ---------------------------------------------------------------------------------
      bool operator< ( Uuid const& rhs ) const;
      // ---------------------------------------------------------------------------------
      Uuid & operator= ( Uuid const& rhs );
      // ---------------------------------------------------------------------------------
      bool operator== ( Uuid const& rhs ) const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      QUuid _M_impl;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  typedef QList<Uuid> UuidList;
  // ---------------------------------------------------------------------------------
  inline Uuid uuid()
  {
    return Uuid();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_UUID_H
