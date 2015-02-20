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

#include "kreporttablemodel.h"

namespace dp
{
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KReportTableModel::KReportTableModel ( QObject* parent )
    :QAbstractTableModel(parent)
    {
    }
    // ---------------------------------------------------------------------------------
    QVariant KReportTableModel::data ( const QModelIndex& index, int role ) const
    {
      if(!index.isValid()) return QVariant();
      if(role == SortRole) return _M_report.reportData().rawData(index);
      if(role != Qt::DisplayRole) return QVariant();
      return _M_report.reportData().data(index);
    }
    // ---------------------------------------------------------------------------------
    int KReportTableModel::columnCount ( const QModelIndex& parent ) const
    {
      return _M_report.reportData().columnCount();
    }
    // ---------------------------------------------------------------------------------
    int KReportTableModel::rowCount ( const QModelIndex& parent ) const
    {
      return _M_report.reportData().rowCount();
    }
    // ---------------------------------------------------------------------------------
    QVariant KReportTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
    {
      if(orientation != Qt::Horizontal) return QVariant();
      if(role != Qt::DisplayRole) return QVariant();
      return _M_report.reportData().header(section);
    }
    // ---------------------------------------------------------------------------------
    Report const& KReportTableModel::report() const
    {
      return _M_report;
    }
    // ---------------------------------------------------------------------------------
    void KReportTableModel::setReport ( const dp::Report& data )
    {
      _M_report = data;
      beginResetModel();
      endResetModel();
    }
    // ---------------------------------------------------------------------------------
    void KReportTableModel::resetReport()
    {
      _M_report = Report();
      beginResetModel();
      endResetModel();
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
