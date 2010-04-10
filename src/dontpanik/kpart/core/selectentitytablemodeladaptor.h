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

#ifndef DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H
#define DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <QObject>
// ---------------------------------------------------------------------------------
class QModelIndex;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectEntityTableModelAdaptor
    : public QObject
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModelAdaptor ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
        virtual ~SelectEntityTableModelAdaptor();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        virtual QVariant data ( const QModelIndex& index ) const=0;
        virtual int columnCount ( ) const=0;
        virtual int rowCount ( ) const=0;
        virtual QVariant headerData ( int column )const=0;
        // ---------------------------------------------------------------------------------
        virtual UuidList selected() const = 0;
        // ---------------------------------------------------------------------------------
        virtual void setSelected(UuidList const&) = 0;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //DP_CORE_SELECTENTITYTABLEMODELADAPTOR_H