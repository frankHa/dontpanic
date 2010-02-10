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

#include "kprojectstable.h"
#include "kprojectstablemodel.h"
#include "context.h"
#include <KMessageBox>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KProjectsTable::KProjectsTable ( QWidget *parent )
        : QTableView ( parent )
        , _M_model ( new detail::KProjectsTableModel ( this ) )
        , _M_sort_proxy_model(new QSortFilterProxyModel(this))
    {
      _M_sort_proxy_model->setSourceModel(_M_model);
      setModel ( _M_sort_proxy_model );
      resizeColumnsToContents();
      this->sortByColumn(0, Qt::AscendingOrder);
    }
    // ---------------------------------------------------------------------------------
    void KProjectsTable::on_remove_selected_project()
    {
      Project const& current_selection = _M_model->at(_M_sort_proxy_model->mapToSource(currentIndex()));  
      if(KMessageBox::questionYesNo(this, i18n("Do you really want to remove the selected project?"), i18n("Remove Project"))==KMessageBox::Yes)
      {
        context()->projectManager()->remove(current_selection);
      }
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
