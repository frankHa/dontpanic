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

#include "ktaskstable.h"
#include "ktaskstablemodel.h"
#include "kedittaskdialog.h"
#include "context.h"
#include <KMessageBox>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KTasksTable::KTasksTable ( QWidget *parent )
        : QTableView ( parent )
        , _M_model ( new detail::KTasksTableModel ( this ) )
        , _M_sort_proxy_model(new QSortFilterProxyModel(this))
    {
      _M_sort_proxy_model->setSourceModel(_M_model);
      setModel ( _M_sort_proxy_model );
      resizeColumnsToContents();
      this->sortByColumn(0, Qt::AscendingOrder);
      connect(this, SIGNAL(doubleClicked(QModelIndex const&)), SLOT(on_edit_selected_task()));
    }
    // ---------------------------------------------------------------------------------
    void KTasksTable::on_remove_selected_task()
    {
      Task const& current_selection = _M_model->at(_M_sort_proxy_model->mapToSource(currentIndex()));  
      if(KMessageBox::questionYesNo(this, i18n("Do you really want to remove the selected task description?"), i18n("Remove Task Description"))==KMessageBox::Yes)
      {
        context()->taskManager()->remove(current_selection);
      }
    }
    // ---------------------------------------------------------------------------------
    void KTasksTable::on_edit_selected_task()
    {
      Task const& current_selection = _M_model->at(_M_sort_proxy_model->mapToSource(currentIndex()));  
      KEditTaskDialog dlg;
      dlg.setTask(current_selection);
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
