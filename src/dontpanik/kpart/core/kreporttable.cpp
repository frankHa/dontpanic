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

#include "kreporttable.h"
#include "kreporttablemodel.h"
#include <QSortFilterProxyModel>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KReportTable::KReportTable ( QWidget* parent ) 
    : QTableView ( parent )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::setReport ( ReportData const& data )
    {
      _M_data_model->setReport(data);
      this->resizeColumnsToContents();
    }
    // ---------------------------------------------------------------------------------
    void KReportTable::resetReport ()
    {
      _M_data_model->resetReport();
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KReportTable::init()
    {
      _M_data_model = new KReportTableModel(this);
      _M_sort_model = new QSortFilterProxyModel(this);
      _M_sort_model->setSourceModel(_M_data_model);
      this->setModel(_M_sort_model);
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

