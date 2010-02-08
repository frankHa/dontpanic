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
#include "kactionstablecolumns.h"
#include "context.h"
#include <libdontpanic/durationformatter.h>
#include <QFont>
#include <KLocalizedString>
#include <KDebug>
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
      class TimeFormatter
      {
        public:
          QString start(Action const& a)
          {
            return a.startTime().time().toString(Qt::SystemLocaleShortDate);
          }
          QString end(Action const& a)
          {
            QString anotherDayMarker("");
            if(a.startTime().date().day()<a.endTime().date().day())
            {
              anotherDayMarker = ">";
            }
            QString result = QString("%1%2").arg(anotherDayMarker).arg(a.endTime().time().toString(Qt::SystemLocaleShortDate));
            return result;
          }
      };
      TimeFormatter time_formatter(){return TimeFormatter();}
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
        if(!index.isValid())return QVariant();
        Action const&a = _M_actions.value(index.row());
        switch(role)
        {
          case Qt::FontRole: return font_role(a, index);
          case Qt::DisplayRole: return display_role(a, index);
          case Qt::EditRole: return edit_role(a, index);
          case Qt::ToolTipRole : return tooltip_role(a, index);
          default: return QVariant();
        }
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::tooltip_role(Action const& a, QModelIndex const& index) const
      {
        DurationFormatter d;
        QString tt = QString(i18n("This Task:\t%1\nToday:\t%2\nuuid:\t:%3")).arg(d.format(a.duration())).arg(d.format(duration())).arg(a.id().toString());
        return tt;
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::display_role(Action const& a, QModelIndex const& index) const
      {
        switch(index.column())
        {
          case START: return time_formatter().start(a);
          case END:   return time_formatter().end(a);
          case TITLE: return a.name();
          case TYPE:  return task_of(a);
          case PROJECT: return project_of(a);
          case COMMENT: return a.comment();
          default: return QVariant();
        }
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::edit_role(Action const& a, QModelIndex const& index) const
      {
        switch(index.column())
        {
          case START: return a.startTime();
          case END:   return a.endTime();
          case TITLE: return a.name();
          case TYPE:  return a.task().toString();
          case PROJECT: return a.project().toString();
          case COMMENT: return a.comment();
          default: return QVariant();
        }
      }
      // ---------------------------------------------------------------------------------
      QVariant KActionsTableModel::font_role(Action const& a, QModelIndex const& index) const
      {
        QFont _font;
        if(a.isActive())
        {
          _font.setBold(true);
        }
        return _font;
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
        if(!index.isValid()) return false;
        if(role != Qt::EditRole) return true;
        Action a = at(index);
        switch(index.column())
        {
          case START: a.setStartTime(value.toDateTime());break;
          case END:   a.setEndTime(value.toDateTime()); break;
          case TITLE: a.setName(value.toString()); break;
          case TYPE:  a.setTask(value.toString()); break;
          case PROJECT: a.setProject(value.toString()); break;
          case COMMENT: a.setComment(value.toString()); break;
          default: break;
        }
        context()->timeTracker()->store(a);
        return true;
      }
      // ---------------------------------------------------------------------------------
      Qt::ItemFlags KActionsTableModel::flags ( const QModelIndex & index ) const
      {
        Qt::ItemFlags _flags = QAbstractItemModel::flags(index);
        _flags |= Qt::ItemIsEditable;
        return ( _flags);
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
      Action KActionsTableModel::at(QModelIndex const& index) const
      {
        if(!index.isValid()){return NullAction();}
        return _M_actions.value(index.row());
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
      int KActionsTableModel::duration() const
      {
        int result = 0;
        ActionList::const_iterator iter;
        for(iter = _M_actions.begin();iter != _M_actions.end();++iter)
        {
          result += iter->duration();
        }
        return result;
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
        kDebug()<<p.id().toString()<< ", start time:"<<p.startTime();
        if(!is_interesting_for_current_day(p)){return;}
        int index = _M_actions.size();
        beginInsertRows(QModelIndex(), index, index);
        _M_actions.append(p);
        endInsertRows();
      }   
      // ---------------------------------------------------------------------------------
      void KActionsTableModel::updated(dp::Action const&p)
      {
        kDebug()<<p.id().toString()<< ", start time:"<<p.startTime();
        if(!is_interesting_for_current_day(p))
        {
          removed(p);
          return;
        }
        int row = _M_actions.indexOf(p);
        QModelIndex const& begin = index(row, START);
        QModelIndex const& end = index(row, COMMENT);
        _M_actions.replace(row, p);
        emit dataChanged(begin, end);
      }   
      // ---------------------------------------------------------------------------------
      bool KActionsTableModel::is_interesting_for_current_day(dp::Action const& a)
      {
        if(!_M_current_day.isValid()){return false;}
        bool result = a.startTime().date() == _M_current_day;
        return result;
      }
      // ---------------------------------------------------------------------------------
      QString KActionsTableModel::project_of(Action const& a) const
      {
        if(a.project().isNull()){return "";}
        return context()->projectManager()->load(a.project()).name();
      }
      // ---------------------------------------------------------------------------------
      QString KActionsTableModel::task_of(Action const& a) const
      {
        if(a.task().isNull()){return "";}
        return context()->taskManager()->load(a.task()).name();
      }
      // ---------------------------------------------------------------------------------
    }//detail
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
