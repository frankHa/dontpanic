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

#include "kreporttypeslistmodel.h"
#include "context.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      // ---------------------------------------------------------------------------------
      enum{NAME, DATE};
      // ---------------------------------------------------------------------------------
      KReportTypesListModel::KReportTypesListModel ( QObject *parent )
          : QAbstractListModel ( parent )
      {
        init_header_data();
        init_report_types_list();	
      }
      // ---------------------------------------------------------------------------------
      QVariant KReportTypesListModel::data ( const QModelIndex& index, int role ) const
      {
        if(!index.isValid()) return QVariant();
        if(role != Qt::DisplayRole) return QVariant();
        return _M_report_types.value(index.row()).name();        
      }
      // ---------------------------------------------------------------------------------
      QVariant KReportTypesListModel::headerData ( int section, Qt::Orientation orientation, int role ) const
      {
        if ( role != Qt::DisplayRole )
        {          
          return QVariant();
        }
        if ( orientation != Qt::Horizontal )
        {
          return QVariant();
        }
        return _M_headers.at ( section );
      }
      // ---------------------------------------------------------------------------------
      int KReportTypesListModel::rowCount ( const QModelIndex& parent ) const
      {
        return _M_report_types.size();
      }
      // ---------------------------------------------------------------------------------
      ReportType KReportTypesListModel::at(QModelIndex const& index) const
      {
        if(!index.isValid()) return NullReportType();
        return _M_report_types.value(index.row());
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::init_header_data()
      {
        _M_headers << i18n ( "Name" )
        << i18n ( "Creation Date" );
      }
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::init_report_types_list()
      {
        //_M_report_types<< i18n("cf monthly report");
        _M_report_types = context()->reportManager()->allReportTypes();
      }
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
