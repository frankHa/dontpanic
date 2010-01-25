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
#include "context.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <KAction>
#include <KMessageBox>
#include <KDebug>
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
      connect(this, SIGNAL(doubleClicked(QModelIndex const&)), SLOT(on_double_clicked(QModelIndex const&)));
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::init_menu_actions()
    {
      _M_new_action_template = new KAction("Create new Favorite", this);
      connect(_M_new_action_template, SIGNAL(triggered()), this, SLOT(on_create_new_action_template()));
      _M_edit_selected_action_template = new KAction("Edit", this);
      connect(_M_edit_selected_action_template, SIGNAL(triggered()), this, SLOT(on_edit_selected_action_template()));
      _M_remove_selected_action_template = new KAction("Remove", this);
      connect(_M_remove_selected_action_template, SIGNAL(triggered()), this, SLOT(on_remove_selected_action_template()));
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
        menu.addAction(_M_remove_selected_action_template);
      }
      menu.exec(evt->globalPos());      
    }
    // ---------------------------------------------------------------------------------
    void KActionTemplatesList::on_double_clicked(QModelIndex const& index)
    {
      ActionTemplate const& at = _M_model->at(index);
      kDebug()<<"starting action from template "<<at.id().toString();
      context()->timeTracker()->startActionFromTemplate(at);
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
    void KActionTemplatesList::on_remove_selected_action_template()
    {
      ActionTemplate current_selection = _M_model->at(currentIndex());  
      if(KMessageBox::questionYesNo(this, "Do you really want to remove the selected favorite definition?", "Remove Favorite")==KMessageBox::Yes)
      {
        kDebug()<<"attempting to delete action template "<<current_selection.id().toString();
        context()->actionTemplateManager()->remove(current_selection);
      }
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
