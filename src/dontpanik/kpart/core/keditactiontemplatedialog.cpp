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

#include "keditactiontemplatedialog.h"
#include "ui_keditactiontemplatedialog.h"
#include "context.h"
#include <QVariant>
#include <KDebug>
namespace dp
{
   namespace core
   {
     KEditActionTemplateDialog::KEditActionTemplateDialog(QWidget *parent)
     :QDialog(parent)
     , _M_ui(new Ui::KEditActionTemplateDialog())
     {
       _M_ui->setupUi(this);
       _M_ui->icon->setIconType(KIconLoader::NoGroup, KIconLoader::Emote);
       setup_actions();
       init_combo_boxes();
     }
     
     KEditActionTemplateDialog::~KEditActionTemplateDialog()
     {
       delete _M_ui;
     }
     
     void KEditActionTemplateDialog::setup_actions()
     {
       connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
       connect(_M_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
     }
     
     void KEditActionTemplateDialog::init_combo_boxes()
     {
       init_projects();
       init_tasks();
     }
     
     void KEditActionTemplateDialog::init_projects()
     {
       ProjectList projects = context()->projectManager()->allProjects();
       ProjectList::const_iterator it;
       for(it=projects.begin();it!=projects.end();++it)
       {
         _M_ui->projects->addItem(it->name(), it->id().toString());
       }
     }
     
     void KEditActionTemplateDialog::init_tasks()
     {
       TaskList tasks = context()->taskManager()->allTasks();
       TaskList::const_iterator it;
       for(it=tasks.begin();it!=tasks.end();++it)
       {
         _M_ui->worktype->addItem(it->name(), it->id().toString());
       }
     }
     
     void KEditActionTemplateDialog::accepted()
     {
       kDebug()<<"";
       QString const& name = _M_ui->name->text();
       if(!name.isEmpty())
       {
         dp::ActionTemplate t(name);
         QUuid project(_M_ui->projects->itemData(_M_ui->projects->currentIndex()).toString());
         QUuid task(_M_ui->worktype->itemData(_M_ui->projects->currentIndex()).toString());
         t.setProject(project);
         t.setTask(task);
         t.setComment(_M_ui->comment->text());
         context()->actionTemplateManager()->store(t);
       }
     }
     
     void KEditActionTemplateDialog::rejected()
     {
       close();
     }
   }//core
}//dp