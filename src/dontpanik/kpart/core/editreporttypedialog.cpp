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

#include "editreporttypedialog.h"
#include "ui_editreporttypedialog.h"
#include "context.h"
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    EditReportTypeDialog::EditReportTypeDialog ( QWidget* parent, Qt::WindowFlags f)
    :QDialog(parent, f)
    ,_M_ui(new Ui::EditReportTypeDialog)
    , _M_current_report_type(NullReportType())
    {
        _M_ui->setupUi(this);
        _M_ui->icon->setIconType(KIconLoader::NoGroup, KIconLoader::Emote);
        setup_actions();
    }
    // ---------------------------------------------------------------------------------
    EditReportTypeDialog::~EditReportTypeDialog()
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::setReportType(ReportType const& at)
    {
      if(!at.isValid()){return;}
      _M_current_report_type = at;
      _M_ui->name->setText(at.name());
      _M_ui->icon->setIcon(at.icon());
      _M_ui->group_tasks->setChecked(at.groupByTask());
      _M_ui->group_projects->setChecked(at.groupByProject());
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::setup_actions()
    {
      connect(_M_ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
      connect(_M_ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::accepted()
    {
      kDebug()<<"";
      QString const& name = _M_ui->name->text();
      if(!name.isEmpty())
      {
        ReportType t;
        if(_M_current_report_type.isValid())
        {
          t = _M_current_report_type;
        }
        t.setName(_M_ui->name->text());   
        t.setIcon(_M_ui->icon->icon());
        t.setGroupByProject(_M_ui->group_projects->isChecked());
        t.setGroupByTask(_M_ui->group_tasks->isChecked());
        context()->reportManager()->store(t);
      }
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::rejected()
    {
      close();
    }
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#include <editreporttypedialog.moc>
