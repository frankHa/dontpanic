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

#ifndef KACTIONTEMPLATESLIST_H
#define KACTIONTEMPLATESLIST_H

#include <QListView>
// ---------------------------------------------------------------------------------
class KAction;
class QMenu;
// ---------------------------------------------------------------------------------
namespace dp
{
  namespace core
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      // ---------------------------------------------------------------------------------
      class KActionTemplatesListModel;
      // ---------------------------------------------------------------------------------
    }
    // ---------------------------------------------------------------------------------
    class KActionTemplatesList
          : public QListView
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KActionTemplatesList ( QWidget* parent = 0 );
        // ---------------------------------------------------------------------------------        
      protected slots:
        // ---------------------------------------------------------------------------------
        virtual void contextMenuEvent(QContextMenuEvent* evt);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_create_new_action_template();
        // ---------------------------------------------------------------------------------
        void on_edit_selected_action_template();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init_menu_actions();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        detail::KActionTemplatesListModel *_M_model;
        // ---------------------------------------------------------------------------------
        KAction *_M_new_action_template;
        // ---------------------------------------------------------------------------------
        KAction *_M_edit_selected_action_template;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

#endif // KACTIONTEMPLATESTABLE_H
