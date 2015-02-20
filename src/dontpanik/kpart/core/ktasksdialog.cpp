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

#include "ktasksdialog.h"
#include "ui_ktasksdialog.h"
#include <kedittaskdialog.h>
namespace dp
{
  namespace core
  {
    KTasksDialog::KTasksDialog ( QWidget* parent, Qt::WindowFlags f )
        : QDialog ( parent, f )
        , _M_ui ( new Ui::KTasksDialog() )
    {
      _M_ui->setupUi(this);
      setWindowTitle(i18n("Tasks/Worktypes"));
      //setInitialSize(QSize(470, 460));
      setup_actions();
    }

    KTasksDialog::~KTasksDialog ( )
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void KTasksDialog::setup_actions()
    {
      connect(_M_ui->b_add, SIGNAL(clicked()), this, SLOT(add()));
      connect(_M_ui->b_remove, SIGNAL(clicked()), _M_ui->tableView, SLOT(on_remove_selected_task()));
      connect(_M_ui->buttons, SIGNAL(rejected()), this, SLOT(accept()));
    }
    // ---------------------------------------------------------------------------------
    void KTasksDialog::add()
    {
      KEditTaskDialog dlg(this);
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
  }
}

