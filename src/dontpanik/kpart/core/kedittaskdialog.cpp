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

#include "kedittaskdialog.h"
#include "ui_kedittaskdialog.h"
#include <libdontpanic/task.hpp>
#include "context.h"
#include <KDebug>
namespace dp
{
  namespace core
  {
    KEditTaskDialog::KEditTaskDialog(QWidget *parent)
    :QDialog(parent)
    , _M_ui (new Ui::KEditTaskDialog())
    {
      _M_ui->setupUi(this);
      setup_actions();
    }
    KEditTaskDialog::~KEditTaskDialog()
    {
      delete _M_ui;
    }
    
    void KEditTaskDialog::setup_actions()
    {
      connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
      connect(_M_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    }
    
    void KEditTaskDialog::accepted()
    {
      kDebug()<<"";
      QString const& name = _M_ui->task_name->text();
      if(!name.isEmpty())
      {
	dp::Task p(name);
	context()->taskManager()->store(p);
      }
    }
    void KEditTaskDialog::rejected()
    {
      close();
    }
  }//core
}//dp

