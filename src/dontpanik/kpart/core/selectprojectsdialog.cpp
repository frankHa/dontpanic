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

#include "selectprojectsdialog.h"
#include "selectprojectsdialog.moc"
#include "ui_selectprojectsdialog.h"
#include "selectentitytablemodel.h"
#include "selectprojectstablemodeladaptor.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    SelectProjectsDialog::SelectProjectsDialog ( QWidget* parent, Qt::WindowFlags f ) 
    : QDialog ( parent, f )
    , _M_ui(new Ui::SelectProjectsDialog())
    {
      _M_ui->setupUi(this);
      init_model();
    }
    // ---------------------------------------------------------------------------------
    SelectProjectsDialog::~SelectProjectsDialog()
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    //private stuff:
    // ---------------------------------------------------------------------------------
    void SelectProjectsDialog::init_model()
    {
      _M_model = new SelectEntityTableModel(new SelectProjectsTableModelAdaptor(), this);
      _M_ui->projects_table->setModel(_M_model);
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------

