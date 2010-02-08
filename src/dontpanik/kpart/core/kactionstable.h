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

#ifndef DP_KACTIONSTABLE_H
#define DP_KACTIONSTABLE_H

#include <QtGui/QTableView>
#include <QSortFilterProxyModel>
#include <kactionstablemodel.h>
#include <KAction>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      class KActionsTableModel;
    }//detail
    // ---------------------------------------------------------------------------------
    class KActionsTable : public QTableView
    {
        Q_OBJECT
      public:
        KActionsTable ( QWidget *parent = 0 );
        
      public slots:
        // ---------------------------------------------------------------------------------
        void load_actions_of(QDate const& day);
        // ---------------------------------------------------------------------------------
       protected slots:
        // ---------------------------------------------------------------------------------
        virtual void contextMenuEvent(QContextMenuEvent* evt);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_remove_selected_action();
        // ---------------------------------------------------------------------------------
        void on_edit_selected_action();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_model();
        // ---------------------------------------------------------------------------------
        void init_menu_actions();
        // ---------------------------------------------------------------------------------
        void init_item_delegate();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        detail::KActionsTableModel *_M_model;
        QSortFilterProxyModel *_M_sort_proxy_model;
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        bool eventFilter(QObject *obj, QEvent *e);
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        KAction *_M_remove_selected_action;
        // ---------------------------------------------------------------------------------
        KAction *_M_edit_selected_action;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

#endif // DP_KACTIONSTABLE_H
