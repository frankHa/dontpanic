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

#include "kactiontemplateslist.h"
#include "kactiontemplateslistmodel.h"
#include "keditactiontemplatedialog.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <KAction>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KActionTemplatesList::KActionTemplatesList ( QWidget *parent )
        : QListView ( parent )
        , _M_model ( new detail::KActionTemplatesListModel ( this ) )
    {
      setModel ( _M_model );
      init_menu_actions();
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::init_menu_actions()
    {
      _M_new_action_template = new KAction("Create new Favorite", this);
      connect(_M_new_action_template, SIGNAL(triggered()), this, SLOT(on_create_new_action_template()));
      _M_edit_selected_action_template = new KAction("Edit", this);
      connect(_M_edit_selected_action_template, SIGNAL(triggered()), this, SLOT(on_edit_selected_action_template()));
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::contextMenuEvent(QContextMenuEvent *evt)
    {
      QMenu menu;
      menu.addAction(_M_new_action_template);
      if(this->selectionModel()->hasSelection())
      {
        menu.addSeparator();
        menu.addAction(_M_edit_selected_action_template);
      }
      menu.exec(evt->globalPos());      
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::on_create_new_action_template()
    {
      KEditActionTemplateDialog dlg;
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::on_edit_selected_action_template()
    {
      ActionTemplate current_selection = _M_model->at(currentIndex());
      KEditActionTemplateDialog dlg;
      dlg.setActionTemplate(current_selection);
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
