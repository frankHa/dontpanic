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

namespace dp
{
   namespace core
   {
     KEditActionTemplateDialog::KEditActionTemplateDialog(QWidget *parent)
     :QDialog(parent)
     , _M_ui(new Ui::KEditActionTemplateDialog())
     {
       _M_ui->setupUi(this);
       setup_actions();
     }
     
     KEditActionTemplateDialog::~KEditActionTemplateDialog()
     {
       delete _M_ui;
     }
     
     void KEditActionTemplateDialog::setup_actions()
     {
     }
     
     void KEditActionTemplateDialog::accepted()
     {
     }
     
     void KEditActionTemplateDialog::rejected()
     {
     }
   }//core
}//dp