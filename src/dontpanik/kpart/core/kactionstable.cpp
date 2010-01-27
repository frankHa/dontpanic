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
    }
    // ---------------------------------------------------------------------------------
    void KActionsTable::load_actions_of(QDate const& day)
    {
      _M_model->set_current_day(day);
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
  }//core
  // ---------------------------------------------------------------------------------
}//dp

