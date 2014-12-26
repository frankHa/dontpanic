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
namespace dp
{
   namespace core
   {
     KEditActionTemplateDialog::KEditActionTemplateDialog(QWidget *parent)
     :QDialog(parent)
     , _M_ui(new Ui::KEditActionTemplateDialog())
     , _M_current_template(NullActionTemplate())
     {
       _M_ui->setupUi(this);
       setWindowTitle(i18n("Favorite"));
       _M_ui->icon->setIconType(KIconLoader::NoGroup, KIconLoader::Emote);
       setup_actions();
     }
     
     KEditActionTemplateDialog::~KEditActionTemplateDialog()
     {
       delete _M_ui;
     }
     
     void KEditActionTemplateDialog::setActionTemplate(ActionTemplate const& at)
     {
       if(!at.isValid()){return;}
       _M_current_template = at;
       _M_ui->name->setText(at.name());
       _M_ui->comment->setText(at.comment());
       _M_ui->icon->setIcon(at.icon());
       _M_ui->projects->select(at.project());
       _M_ui->worktype->select(at.task());
     }
     
     void KEditActionTemplateDialog::setup_actions()
     {
       connect(_M_ui->buttons, SIGNAL(accepted()), this, SLOT(accepted()));
       connect(_M_ui->buttons, SIGNAL(rejected()), this, SLOT(rejected()));
     }
     
     void KEditActionTemplateDialog::accepted()
     {
       qDebug()<<"";
       QString const& name = _M_ui->name->text();
       if(!name.isEmpty())
       {
         ActionTemplate t;
         if(_M_current_template.isValid())
         {
            t = _M_current_template;
         }
         t.setName(_M_ui->name->text());         
         Uuid project(_M_ui->projects->selectedUuid());
         Uuid task(_M_ui->worktype->selectedUuid());
         t.setProject(project);
         t.setTask(task);
         t.setComment(_M_ui->comment->text());
         t.setIcon(_M_ui->icon->icon());
         context()->actionTemplateManager()->store(t);
       }
       accept();
     }
     
     void KEditActionTemplateDialog::rejected()
     {
       reject();
     }
   }//core
}//dp