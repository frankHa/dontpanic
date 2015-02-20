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

#ifndef KEDITACTIONTEMPLATEDIALOG_H
#define KEDITACTIONTEMPLATEDIALOG_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/actiontemplate.hpp>
#include <QDialog>
namespace Ui
{
  class KEditActionTemplateDialog;
}

class QUuid;
class QComboBox;

namespace dp
{
  namespace core
  {
    class KEditActionTemplateDialog
    : public QDialog
    {
      Q_OBJECT
      public:
        KEditActionTemplateDialog(QWidget *parent=0);
        ~KEditActionTemplateDialog();
      public:
        void setActionTemplate(ActionTemplate const& at);
      private:
        void setup_actions();
        
      private slots:
        void accepted();
        void rejected();
        
      private:
        Ui::KEditActionTemplateDialog *_M_ui;   
        ActionTemplate _M_current_template;
    };
  }
}

#endif // KEDITACTIONTEMPLATEDIALOG_H
