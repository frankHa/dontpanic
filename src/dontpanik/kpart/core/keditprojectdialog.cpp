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

#include "keditprojectdialog.h"
#include "ui_keditprojectdialog.h"
#include <libdontpanic/project.hpp>
#include "context.h"
#include <KDebug>
namespace dp
{
  namespace core
  {
    KEditProjectDialog::KEditProjectDialog(QWidget *parent)
    :QDialog(parent)
    , _M_ui (new Ui::KEditProjectDialog())
    , _M_current_project(NullProject())
    {
      _M_ui->setupUi(this);
      _M_ui->creation_date->setDateTime(QDateTime::currentDateTime());
      setup_actions();
    }
    KEditProjectDialog::~KEditProjectDialog()
    {
      delete _M_ui;
    }
    
    KEditProjectDialog& KEditProjectDialog::setProject(Project const& p)
    {
      _M_current_project = p;
      _M_ui->project_name->setText(p.name());
      _M_ui->creation_date->setDateTime(p.creationDate());
      _M_ui->comment->setText(p.comment());
      return *this;
    }
    
    void KEditProjectDialog::setup_actions()
    {
      connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
      connect(_M_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    }
    
    void KEditProjectDialog::accepted()
    {
      QString const& name = _M_ui->project_name->text();
      Project p;
      if(_M_current_project.isValid())
      {
        p = _M_current_project;
      }
      if(!name.isEmpty())
      {
        p.setName(name)
        .setCreationDate(_M_ui->creation_date->dateTime())
        .setComment(_M_ui->comment->text());
        context()->projectManager()->store(p);
      }
    }
    void KEditProjectDialog::rejected()
    {
      close();
    }
  }//core
}//dp

