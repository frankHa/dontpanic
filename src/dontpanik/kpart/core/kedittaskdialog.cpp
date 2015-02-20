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
namespace dp
{
  namespace core
  {
    KEditTaskDialog::KEditTaskDialog(QWidget *parent)
    :QDialog(parent)
    , _M_ui (new Ui::KEditTaskDialog())
    , _M_current_task(NullTask())
    {
      _M_ui->setupUi(this);
      setWindowTitle(i18n("Worktype"));
      _M_ui->creation_date->setDateTime(QDateTime::currentDateTime());
      setup_actions();
    }
    KEditTaskDialog::~KEditTaskDialog()
    {
      delete _M_ui;
    }
    
    KEditTaskDialog& KEditTaskDialog::setTask(Task const& task)
    {
      _M_current_task = task;
      _M_ui->task_name->setText(task.name());
      _M_ui->visible->setChecked(task.isVisible());      
      _M_ui->creation_date->setDateTime(task.creationDate());
      _M_ui->comment->setText(task.comment());
      return *this;
    }
    
    void KEditTaskDialog::setup_actions()
    {
      connect(_M_ui->buttons, SIGNAL(accepted()), this, SLOT(accepted()));
      connect(_M_ui->buttons, SIGNAL(rejected()), this, SLOT(rejected()));
    }
    
    void KEditTaskDialog::accepted()
    {
      QString const& name = _M_ui->task_name->text();
      Task t;
      if(_M_current_task.isValid())
      {
        t = _M_current_task;
      }
      if(!name.isEmpty())
      {
        t.setName(name)
        .setCreationDate(_M_ui->creation_date->dateTime())
        .setVisible(_M_ui->visible->isChecked())
        .setComment(_M_ui->comment->text());        
        context()->taskManager()->store(t);
      }
      accept();
    }
    void KEditTaskDialog::rejected()
    {
      reject();
    }
  }//core
}//dp

