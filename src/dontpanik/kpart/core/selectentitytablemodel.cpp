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

#include "selectentitytablemodel.h"
#include "selectentitytablemodel.moc"
#include "selectprojectstablemodeladaptor.h"
#include <QSortFilterProxyModel>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    SelectEntityTableModel::SelectEntityTableModel ( SelectEntityTableModelAdaptor * data, QObject* parent )
        : QAbstractTableModel ( parent )
        , _M_data ( data )
    {
      _M_data->setParent ( this );
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectEntityTableModel::data ( const QModelIndex& index, int role ) const
    {
      if ( role == Qt::DisplayRole )
        return _M_data->data ( index );
      if ( role == Qt::CheckStateRole )
      {
        if(!_M_data->isCheckable(index.column())){return QVariant();}
        return _M_data->checkState ( index.row() );
      }
      return QVariant();

    }
    // ---------------------------------------------------------------------------------
    bool SelectEntityTableModel::setData ( const QModelIndex& index, QVariant const& data, int role )
    {
      if ( role != Qt::CheckStateRole ) return false;
      _M_data->setCheckState ( index.row(), data.toInt() );
      return true;
    }
    // ---------------------------------------------------------------------------------
    int SelectEntityTableModel::columnCount ( const QModelIndex& parent ) const
    {
      return _M_data->columnCount();
    }
    // ---------------------------------------------------------------------------------
    int SelectEntityTableModel::rowCount ( const QModelIndex& parent ) const
    {
      return _M_data->rowCount();
    }
    // ---------------------------------------------------------------------------------
    QVariant SelectEntityTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
    {
      if ( orientation != Qt::Horizontal ) return QVariant();
      if ( role != Qt::DisplayRole ) return QVariant();
      return _M_data->headerData ( section );
    }
    // ---------------------------------------------------------------------------------
    Qt::ItemFlags SelectEntityTableModel::flags ( QModelIndex const& index ) const
    {
      Qt::ItemFlags f = QAbstractTableModel::flags ( index );
      if ( _M_data->isCheckable ( index.column() ) )
      {
        f |= Qt::ItemIsUserCheckable;
      }
      return f;
    }
    // ---------------------------------------------------------------------------------
  }
}
// ---------------------------------------------------------------------------------
