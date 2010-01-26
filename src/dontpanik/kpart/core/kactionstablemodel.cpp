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

#include "kactionstablemodel.h"
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
      enum column{START, END, TITLE, TYPE, PROJECT, COMMENT};
      // ---------------------------------------------------------------------------------
      KActionsTableModel::KActionsTableModel ( QObject *parent )
          : QAbstractTableModel ( parent )
      {
        init_header_data();
        subscribe_to_timetracker_signals();
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::data ( const QModelIndex& index, int role ) const
      {
        if(role != Qt::DisplayRole) return QVariant();
        if(!index.isValid())return QVariant();
        Action const&a = _M_actions.value(index.row());
        switch(index.column())
        {
          case START: return a.startTime().time();
          case END:   return a.endTime().time();
          case TITLE: return a.name();
          case TYPE:  return context()->taskManager()->load(a.task()).name();
          case PROJECT: return context()->projectManager()->load(a.project()).name();
          case COMMENT: return a.comment();
          default: return QVariant();
        }
      }
      // ---------------------------------------------------------------------------------
      int KActionsTableModel::columnCount ( const QModelIndex& parent ) const
      {
        return _M_headers.count();
      }
      // ---------------------------------------------------------------------------------
      int KActionsTableModel::rowCount ( const QModelIndex& parent ) const
      {
        return _M_actions.count();
      }
      // ---------------------------------------------------------------------------------
      bool KActionsTableModel::setData ( const QModelIndex& index, const QVariant& value, int role )
      {
        return QAbstractItemModel::setData ( index, value, role );
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
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
      bool KActionsTableModel::setItemData ( const QModelIndex& index, const QMap< int, QVariant >& roles )
      {
        return QAbstractItemModel::setItemData ( index, roles );
      }
      // ---------------------------------------------------------------------------------
      bool KActionsTableModel::insertRows ( int row, int count, const QModelIndex& parent )
      {
        return QAbstractItemModel::insertRows ( row, count, parent );
      }
      // ---------------------------------------------------------------------------------
      bool KActionsTableModel::removeRows ( int row, int count, const QModelIndex& parent )
      {
        return QAbstractItemModel::removeRows ( row, count, parent );
      }      
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::set_current_day(QDate const& day)
      {
        _M_current_day = day;
        _M_actions=context()->timeTracker()->findAll(day);
        reset();
      }
      // ---------------------------------------------------------------------------------
      //private stuff:
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::init_header_data()
      {
        _M_headers << i18n ( "Start" )
        << i18n ( "End" )
        << i18n ( "Title" )
        << i18n ( "Type" )
        << i18n ( "Project" )
        << i18n ( "Comment" );
      }
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::subscribe_to_timetracker_signals()
      {
        client::TimeTracker * pm = context()->timeTracker();
        connect(pm, SIGNAL(stored(dp::Action)), this, SLOT(stored(dp::Action const&)));
        connect(pm, SIGNAL(removed(dp::Action)), this, SLOT(removed(dp::Action const&)));
      }
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::stored(dp::Action const&p)
      {
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
      void KActionsTableModel::removed(dp::Action const&p)
      {
        int i = _M_actions.indexOf(p);
        beginRemoveRows(QModelIndex(), i, i);
        _M_actions.removeAt(i);
        endRemoveRows();
      }
      // ---------------------------------------------------------------------------------
      bool KActionsTableModel::is_already_known(dp::Action const&p) const
      {
        return (_M_actions.indexOf(p)!=-1);
      }   
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::added(dp::Action const&p)
      {
        if(p.startTime().date()!= _M_current_day){return;}
        int index = _M_actions.size();
        beginInsertRows(QModelIndex(), index, index);
        _M_actions.append(p);
        endInsertRows();
      }   
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::updated(dp::Action const&p)
      {
        if(p.startTime().date() != _M_current_day)
        {
          removed(p);
          return;
        }        
        int row = _M_actions.indexOf(p);
        QModelIndex const& i = index(row, 0);
        _M_actions.replace(row, p);
        emit dataChanged(i, i);
      }   
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
