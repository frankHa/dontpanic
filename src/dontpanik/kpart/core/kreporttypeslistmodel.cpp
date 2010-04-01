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
#include <QPixmap>
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
          , _M_icon_loader ( new KIconLoader ( "", 0, this ) )
      {
        init_header_data();
        subscribe_to_report_manager_signals();
        init_report_types_list();	
      }
      // ---------------------------------------------------------------------------------
      QVariant KReportTypesListModel::data ( const QModelIndex& index, int role ) const
      {
        if ( !index.isValid() ) return QVariant();
        ReportType const& p = _M_report_types.at ( index.row() );
        switch ( role )
        {
          case Qt::DisplayRole: return p.name();
          case Qt::DecorationRole: return _M_icon_loader->loadIcon ( p.icon(), KIconLoader::NoGroup, KIconLoader::SizeMedium );
          default: return QVariant();
        }
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
        _M_report_types = context()->reportManager()->allReportTypes();
      }
      // ---------------------------------------------------------------------------------      
      void KReportTypesListModel::subscribe_to_report_manager_signals()
      {
        client::ReportManager * pm = context()->reportManager();
        connect ( pm, SIGNAL ( stored ( dp::ReportType ) ), this, SLOT ( stored ( dp::ReportType const& ) ) );
        connect ( pm, SIGNAL ( removed ( dp::ReportType ) ), this, SLOT ( removed ( dp::ReportType const& ) ) );
      }
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::stored ( dp::ReportType const&p )
      {
        qWarning() << __FUNCTION__;
        if ( is_already_known ( p ) )
        {
          updated ( p );
        }
        else
        {
          added ( p );
        }
      }
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::removed ( dp::ReportType const&p )
      {
        int i = _M_report_types.indexOf ( p );
        beginRemoveRows ( QModelIndex(), i, i );
        _M_report_types.removeAt ( i );
        endRemoveRows();
      }
      // ---------------------------------------------------------------------------------
      bool KReportTypesListModel::is_already_known ( dp::ReportType const&p ) const
      {
        return ( _M_report_types.indexOf ( p ) != -1 );
      }
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::added ( dp::ReportType const&p )
      {
        int index = _M_report_types.size();
        beginInsertRows ( QModelIndex(), index, index );
        _M_report_types.append ( p );
        endInsertRows();
      }
      // ---------------------------------------------------------------------------------
      void KReportTypesListModel::updated ( dp::ReportType const&p )
      {
        int row = _M_report_types.indexOf ( p );
        kDebug() << "updating report type [" << row << "]";
        QModelIndex const& i = index ( row );
        _M_report_types.replace ( row, p );
        emit dataChanged ( i, i );
      }
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
