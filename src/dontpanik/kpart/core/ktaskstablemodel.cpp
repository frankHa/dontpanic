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

#include "ktaskstablemodel.h"
#include <KLocalizedString>
#include <context.h>
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
      KTasksTableModel::KTasksTableModel ( QObject *parent )
          : QAbstractTableModel ( parent )
      {
        init_header_data();
	subscribe_to_task_manager_signals();
        init_tasks_list();	
      }
      // ---------------------------------------------------------------------------------
      QVariant KTasksTableModel::data ( const QModelIndex& index, int role ) const
      {
        if(!index.isValid())return QVariant();
	if(role != Qt::DisplayRole) return QVariant();
	Task const& p = _M_tasks.at(index.row());
	switch(index.column())
	{
	  case NAME: return p.name();
	  case DATE: return p.creationDate();
	  default: return QVariant();
	}
      }
      // ---------------------------------------------------------------------------------
      QVariant KTasksTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
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
      int KTasksTableModel::columnCount ( const QModelIndex& parent ) const
      {
        return _M_headers.count();
      }
      // ---------------------------------------------------------------------------------
      int KTasksTableModel::rowCount ( const QModelIndex& parent ) const
      {
        return _M_tasks.size();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::init_header_data()
      {
        _M_headers << i18n ( "Name" )
        << i18n ( "Creation Date" );
      }
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::init_tasks_list()
      {
        _M_tasks = context()->taskManager()->allTasks();
      }
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::subscribe_to_task_manager_signals()
      {
	client::TaskManager * pm = context()->taskManager();
        connect(pm, SIGNAL(stored(dp::Task)), this, SLOT(stored(dp::Task const&)));
	connect(pm, SIGNAL(removed(dp::Task)), this, SLOT(removed(dp::Task const&)));
      }
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::stored(dp::Task const&p)
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
      void KTasksTableModel::removed(dp::Task const&p)
      {
	int i = _M_tasks.indexOf(p);
	beginRemoveRows(QModelIndex(), i, i);
	_M_tasks.removeAt(i);
	endRemoveRows();
      }
      // ---------------------------------------------------------------------------------
      bool KTasksTableModel::is_already_known(dp::Task const&p) const
      {
	return (_M_tasks.indexOf(p)!=-1);
      }	  
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::added(dp::Task const&p)
      {
	int index = _M_tasks.size();
	beginInsertRows(QModelIndex(), index, index);
	_M_tasks.append(p);
	endInsertRows();
      }	  
      // ---------------------------------------------------------------------------------
      void KTasksTableModel::updated(dp::Task const&p)
      {
	int row = _M_tasks.indexOf(p);
	QModelIndex const& i = index(row, NAME);
	dp::Task _p = _M_tasks.at(row);
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
