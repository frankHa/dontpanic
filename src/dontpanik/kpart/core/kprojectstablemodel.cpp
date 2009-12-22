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

#include "kprojectstablemodel.h"
#include "context.h"
#include <KLocalizedString>
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
      KProjectsTableModel::KProjectsTableModel ( QObject *parent )
          : QAbstractTableModel ( parent )
      {
        init_header_data();
        init_projects_list();
      }
      // ---------------------------------------------------------------------------------
      QVariant KProjectsTableModel::data ( const QModelIndex& index, int role ) const
      {
        return QVariant();
      }
      // ---------------------------------------------------------------------------------
      QVariant KProjectsTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
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
      int KProjectsTableModel::columnCount ( const QModelIndex& parent ) const
      {
        return _M_headers.count();
      }
      // ---------------------------------------------------------------------------------
      int KProjectsTableModel::rowCount ( const QModelIndex& parent ) const
      {
        return 0;
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::init_header_data()
      {
        _M_headers << i18n ( "Name" )
        << i18n ( "Creation Date" );
      }
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::init_projects_list()
      {
        ProjectList list = context().projectManager().allProjects();
      }
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
