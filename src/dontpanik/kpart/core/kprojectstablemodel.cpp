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
      enum{NAME, DATE, COMMENT};
      // ---------------------------------------------------------------------------------
      KProjectsTableModel::KProjectsTableModel ( QObject *parent )
          : QAbstractTableModel ( parent )
      {
        init_header_data();
        subscribe_to_project_manager_signals();
        init_projects_list();	
      }
      // ---------------------------------------------------------------------------------
      QVariant KProjectsTableModel::data ( const QModelIndex& index, int role ) const
      {
        if(!index.isValid())return QVariant();
        if(role != Qt::DisplayRole) return QVariant();
        Project const& p = _M_projects.at(index.row());
        switch(index.column())
        {
          case NAME: return p.name();
          case DATE: return p.creationDate();
          case COMMENT: return p.comment();
          default: return QVariant();
        }
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
        return _M_projects.size();
      }
      // ---------------------------------------------------------------------------------
      Project KProjectsTableModel::at(QModelIndex const& index) const
      {
        if(!index.isValid()){return NullProject();}
        return _M_projects.value(index.row());
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::init_header_data()
      {
        _M_headers << i18n ( "Name" )
        << i18n ( "Creation Date" )
        << i18n("Comment");
      }
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::init_projects_list()
      {
        _M_projects = context()->projectManager()->allProjects();
      }
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::subscribe_to_project_manager_signals()
      {
        client::ProjectManager * pm = context()->projectManager();
        connect(pm, SIGNAL(stored(dp::Project)), this, SLOT(stored(dp::Project const&)));
        connect(pm, SIGNAL(removed(dp::Project)), this, SLOT(removed(dp::Project const&)));
      }
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::stored(dp::Project const&p)
      {
        qWarning()<<__FUNCTION__;
        if(is_already_known(p))
        {
          updated(p);
        }
        else
        {
          added(p);
        }
      }
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::removed(dp::Project const&p)
      {
        int i = _M_projects.indexOf(p);
        beginRemoveRows(QModelIndex(), i, i);
        _M_projects.removeAt(i);
        endRemoveRows();
      }
      // ---------------------------------------------------------------------------------
      bool KProjectsTableModel::is_already_known(dp::Project const&p) const
      {
        return (_M_projects.indexOf(p)!=-1);
      }	  
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::added(dp::Project const&p)
      {
        int index = _M_projects.size();
        beginInsertRows(QModelIndex(), index, index);
        _M_projects.append(p);
        endInsertRows();
      }	  
      // ---------------------------------------------------------------------------------
      void KProjectsTableModel::updated(dp::Project const&p)
      {
        int row = _M_projects.indexOf(p);
        QModelIndex const& i = index(row, NAME);
        dp::Project _p = _M_projects.at(row);
        _p.setName(p.name());
        emit dataChanged(i, i);
      }	  
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
