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

#include "kactionstableitemdelegate.h"
#include "kactionstablecolumns.h"
#include "kactionstablemodel.h"
#include "kprojectscombobox.h"
#include "ktaskscombobox.h"

#include <QSortFilterProxyModel>
#include <QTimeEdit>
#include <QCoreApplication>
#include <QShowEvent>
#include <QAbstractItemView>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      // ---------------------------------------------------------------------------------
      KActionsTableItemDelegate::KActionsTableItemDelegate ( QObject* parent )
          : QStyledItemDelegate ( parent )
      {
      }
      // ---------------------------------------------------------------------------------
      QWidget* KActionsTableItemDelegate::createEditor ( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const
      {
        switch ( index.column() )
        {
          case START:
          case END:
          {
            QDateTimeEdit *edit = new QTimeEdit ( parent );
            edit->setCalendarPopup ( true );
            edit->setDisplayFormat("hh:mm");
            return edit;
          }
          case PROJECT:
          {
            KProjectsComboBox *project = new KProjectsComboBox ( parent );
            project->setMouseTracking(true);
            connect ( project, SIGNAL ( popupClosed() ), this, SLOT ( commit_and_close_editor() ) );
            return project;
          }
          case TYPE:
          {
            KTasksComboBox *task = new KTasksComboBox ( parent );
            connect ( task, SIGNAL ( popupClosed() ), this, SLOT ( commit_and_close_editor() ) );
            return task;
          }
          default:return QStyledItemDelegate::createEditor ( parent, option, index );
        }
      }
      // ---------------------------------------------------------------------------------
      void KActionsTableItemDelegate::setEditorData ( QWidget* editor, const QModelIndex& index ) const
      {
        if ( !index.isValid() ) {return;}
        QSortFilterProxyModel const* sm = static_cast<QSortFilterProxyModel const*> ( index.model() );
        QModelIndex const& mappedIndex = sm->mapToSource ( index );
        KActionsTableModel const*model = static_cast<KActionsTableModel const*> ( sm->sourceModel() );
        Action const& a = model->at ( mappedIndex );
        switch ( mappedIndex.column() )
        {
          case START: static_cast<QDateTimeEdit*> ( editor )->setDateTime ( startTimeOf ( a ) ); break;
          case END: static_cast<QDateTimeEdit*> ( editor )->setDateTime ( endTimeOf ( a ) ); break;
          case PROJECT:
          {
            KProjectsComboBox *pb = static_cast<KProjectsComboBox*> ( editor );
            pb->select ( a.project() );
            break;
          }
          case TYPE: static_cast<KTasksComboBox*> ( editor )->select ( a.task() ); break;
          default:QStyledItemDelegate::setEditorData ( editor, index ); break;
        }

      }
      // ---------------------------------------------------------------------------------
      void KActionsTableItemDelegate::setModelData ( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const
      {
        if ( !index.isValid() ) {return;}
        switch ( index.column() )
        {
          case START:
          case END: model->setData ( index, static_cast<QDateTimeEdit*> ( editor )->dateTime() );break;
          case PROJECT: model->setData ( index, static_cast<KProjectsComboBox*> ( editor )->selectedUuid().toString() );break;
          case TYPE:model->setData ( index, static_cast<KTasksComboBox*> ( editor )->selectedUuid().toString() ); break;
          default: QStyledItemDelegate::setModelData ( editor, model, index );break;
        }

      }
      // ---------------------------------------------------------------------------------
      QDateTime KActionsTableItemDelegate::startTimeOf ( Action const& a ) const
      {
        if ( a.startTime().isValid() ) {return a.startTime();}
        if ( a.endTime().isValid() ) {return a.endTime();}
        return QDateTime::currentDateTime();
      }
      // ---------------------------------------------------------------------------------
      QDateTime KActionsTableItemDelegate::endTimeOf ( Action const& a ) const
      {
        if ( a.endTime().isValid() ) {return a.endTime();}
        return QDateTime::currentDateTime();
      }
      // ---------------------------------------------------------------------------------
      void KActionsTableItemDelegate::commit_and_close_editor()
      {
        QWidget *editor = qobject_cast<QWidget *> ( sender() );
        emit commitData ( editor );
        emit closeEditor ( editor );
      }
      // ---------------------------------------------------------------------------------
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
