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

#include "kactionstable.h"
#include "kactionstablemodel.h"
#include "context.h"
#include "kactionstableitemdelegate.h"
#include <QMenu>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <KMessageBox>
#include <KLocalizedString>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KActionsTable::KActionsTable ( QWidget *parent )
        : QTableView ( parent )
        , _M_model ( new detail::KActionsTableModel ( this ))
        , _M_sort_proxy_model(new QSortFilterProxyModel(this))
    {
      init_model();
      init_menu_actions();
      init_item_delegate();
      //verticalHeader()->setDefaultSectionSize(20);
    }
    // ---------------------------------------------------------------------------------
    void KActionsTable::load_actions_of(QDate const& day)
    {
      _M_model->set_current_day(day);
    }
    // ---------------------------------------------------------------------------------
    // protected stuff:
    // ---------------------------------------------------------------------------------
    void KActionsTable::contextMenuEvent(QContextMenuEvent *evt)
    {
      if(!this->selectionModel()->hasSelection()){return;}
      QMenu menu;      
      menu.addAction(_M_remove_selected_action);
      menu.exec(evt->globalPos());      
    }
    
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KActionsTable::init_model()
    {
      _M_sort_proxy_model->setSourceModel(_M_model);
      _M_sort_proxy_model->setDynamicSortFilter(true);
      setModel ( _M_sort_proxy_model );         
      this->sortByColumn(0, Qt::AscendingOrder);
    }
    // ---------------------------------------------------------------------------------
    void KActionsTable::init_menu_actions()
    {
      _M_remove_selected_action = new KAction("Remove", this);
      connect(_M_remove_selected_action, SIGNAL(triggered()), this, SLOT(on_remove_selected_action()));
    }
    // ---------------------------------------------------------------------------------
    void KActionsTable::init_item_delegate()
    {
      detail::KActionsTableItemDelegate *d = new detail::KActionsTableItemDelegate(this);
      setItemDelegate(d);
    }
    // ---------------------------------------------------------------------------------
    void KActionsTable::on_remove_selected_action()
    {
      Action const& current_selection = _M_model->at(_M_sort_proxy_model->mapToSource(currentIndex()));  
      if(KMessageBox::questionYesNo(this, i18n("Do you really want to remove the selected action?"), i18n("Remove Action"))==KMessageBox::Yes)
      {
        context()->timeTracker()->remove(current_selection);
      }
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp

