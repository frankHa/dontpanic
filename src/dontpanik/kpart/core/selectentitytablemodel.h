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

#ifndef DP_CORE_SELECTENTITYTABLEMODEL_H
#define DP_CORE_SELECTENTITYTABLEMODEL_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <QModelIndex>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class SelectEntityTableModelAdaptor;
    // ---------------------------------------------------------------------------------
    class SelectEntityTableModel : public QAbstractTableModel
    {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModel ( SelectEntityTableModelAdaptor *data, QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
        virtual bool setData ( const QModelIndex& index, QVariant const& data, int role = Qt::DisplayRole );
        virtual int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
        virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::EditRole ) const;
        virtual Qt::ItemFlags flags ( QModelIndex const& ) const;
        // ---------------------------------------------------------------------------------
        UuidList selected() const;
        // ---------------------------------------------------------------------------------
        void select(UuidList const& ids);
        // ---------------------------------------------------------------------------------
        void selectAll();
        // ---------------------------------------------------------------------------------
        void unselectAll();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        SelectEntityTableModelAdaptor *_M_data;
        // ---------------------------------------------------------------------------------
    };
  }

}

#endif // DP_CORE_SELECTENTITYTABLEMODEL_H
