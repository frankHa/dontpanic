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

#ifndef DP_CORE_DETAIL_KACTIONSTABLEITEMDELEGATE_H
#define DP_CORE_DETAIL_KACTIONSTABLEITEMDELEGATE_H

#include <QtGui/QStyledItemDelegate>


namespace dp
{
  class Action;
  namespace core
  {

    namespace detail
    {

      class KActionsTableItemDelegate : public QStyledItemDelegate
      {
          Q_OBJECT
        public:
          KActionsTableItemDelegate ( QObject* parent = 0 );
          virtual QWidget* createEditor ( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
          virtual void setEditorData ( QWidget* editor, const QModelIndex& index ) const;
          virtual void setModelData ( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index ) const;

        protected slots:
          void commit_and_close_editor();
        private:
          QDateTime startTimeOf ( Action const& ) const;
          QDateTime endTimeOf ( Action const& ) const;
      };

    }

  }

}

#endif // DP_CORE_DETAIL_KACTIONSTABLEITEMDELEGATE_H
