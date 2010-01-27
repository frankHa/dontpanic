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
     , _M_current_template(NullActionTemplate())
     {
       _M_ui->setupUi(this);
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
       select_project(at.project());
       select_task(at.task());
     }
     
     void KEditActionTemplateDialog::select_project(QUuid const& id)
     {
       kDebug()<<"selecting project: "<<id.toString();
        select(_M_ui->projects, id);
     }
     
     void KEditActionTemplateDialog::select_task(QUuid const& id)
     {
       kDebug()<<"selecting task: "<<id.toString();
       select(_M_ui->worktype, id);
     }
     
     void KEditActionTemplateDialog::select(QComboBox *set, QUuid const& id)
     {
       int index = set->findData(QVariant(id.toString()));
       set->setCurrentIndex(index);
     }
     
     void KEditActionTemplateDialog::setup_actions()
     {
       connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
       connect(_M_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
     }
     
     void KEditActionTemplateDialog::accepted()
     {
       kDebug()<<"";
       QString const& name = _M_ui->name->text();
       if(!name.isEmpty())
       {
         ActionTemplate t;
         if(_M_current_template.isValid())
         {
            t = _M_current_template;
         }
         t.setName(_M_ui->name->text());         
         QUuid project(_M_ui->projects->itemData(_M_ui->projects->currentIndex()).toString());
         QUuid task(_M_ui->worktype->itemData(_M_ui->worktype->currentIndex()).toString());
         t.setProject(project);
         t.setTask(task);
         t.setComment(_M_ui->comment->text());
         t.setIcon(_M_ui->icon->icon());
         context()->actionTemplateManager()->store(t);
       }
     }
     
     void KEditActionTemplateDialog::rejected()
     {
       close();
     }
   }//core
}//dp