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

#ifndef DP_DETAIL_KACTIONSTABLEMODEL_H
#define DP_DETAIL_KACTIONSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace detail
  { 
    // ---------------------------------------------------------------------------------
    class KActionsTableModel : public QAbstractTableModel
    {
      // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KActionsTableModel ( QObject *parent = 0 );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        virtual QVariant data ( const QModelIndex& index, int role = Qt::DisplayRole ) const;
        // ---------------------------------------------------------------------------------
        virtual int columnCount ( const QModelIndex& parent = QModelIndex() ) const;
        // ---------------------------------------------------------------------------------
        virtual int rowCount ( const QModelIndex& parent = QModelIndex() ) const;
        // ---------------------------------------------------------------------------------
        virtual bool setData ( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole );
        // ---------------------------------------------------------------------------------
        virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
        // ---------------------------------------------------------------------------------
        virtual bool setItemData ( const QModelIndex& index, const QMap< int, QVariant >& roles );
        // ---------------------------------------------------------------------------------
        virtual bool insertRows ( int row, int count, const QModelIndex& parent = QModelIndex() );
        // ---------------------------------------------------------------------------------
        virtual bool removeRows ( int row, int count, const QModelIndex& parent = QModelIndex() );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_header_data();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        QStringList _M_headers;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//detail
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif // DP_DETAIL_KACTIONSTABLEMODEL_H
