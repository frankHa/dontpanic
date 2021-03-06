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
#include <libdontpanic/reportdatafiltertype.h>
#include <libdontpanic/reportgroupingtimeinterval.h>
#include "selectprojectsdialog.h"
#include "selecttasksdialog.h"
//Qt includes
#include <QUrl>
#include <QFileDialog>

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
        //setMainWidget(w);
        setWindowTitle(i18n("Report Type"));
        enableButtonOk(false);
        _M_ui->icon->setIconType(KIconLoader::NoGroup, KIconLoader::Emote);
        setup_actions();
        init_combo_boxes();        
    }
    // ---------------------------------------------------------------------------------
    EditReportTypeDialog::~EditReportTypeDialog()
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::enableButtonOk ( bool enabled )
    {
      _M_ui->buttons->button(QDialogButtonBox::Ok)->setEnabled(enabled);
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
      _M_ui->group_timeinterval->setCurrentIndex(at.groupByTimeInterval());
      _M_ui->task_filter_type->setCurrentIndex(at.taskFilter().filterType());
      _M_ui->project_filter_type->setCurrentIndex(at.projectFilter().filterType());
      _M_selected_projects = at.projectFilter().selection();
      _M_ui->export_data_file->setText(at.exportDataFileTemplate());
      _M_selected_tasks = at.taskFilter().selection();
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::setup_actions()
    {
      connect(_M_ui->buttons, SIGNAL(accepted()), this, SLOT(accepted()));
      connect(_M_ui->buttons, SIGNAL(rejected()), this, SLOT(rejected()));
      connect(_M_ui->select_tasks, SIGNAL(clicked()), this, SLOT(select_tasks()));
      connect(_M_ui->select_projects, SIGNAL(clicked()), this, SLOT(select_projects()));
      connect(_M_ui->task_filter_type, SIGNAL(currentIndexChanged(int)), this, SLOT(update_select_tasks_enabled_state(int)));
      connect(_M_ui->project_filter_type, SIGNAL(currentIndexChanged(int)), this, SLOT(update_select_projects_enabled_state(int)));
      connect(_M_ui->select_target_file, SIGNAL(clicked()), this, SLOT(select_target_file()));
      connect(_M_ui->name, SIGNAL(textChanged(QString)), this, SLOT(on_report_name_changed(QString)));
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::init_combo_boxes()
    {
      _M_ui->task_filter_type->addItems(ReportDataFilterType::pretty_names());
      _M_ui->task_filter_type->setCurrentIndex(ReportDataFilterType::NO_FILTER);
      _M_ui->project_filter_type->addItems(ReportDataFilterType::pretty_names());
      _M_ui->project_filter_type->setCurrentIndex(ReportDataFilterType::NO_FILTER);
      _M_ui->group_timeinterval->addItems(ReportGroupingTimeInterval::pretty_names());
      _M_ui->group_timeinterval->setCurrentIndex(ReportGroupingTimeInterval::NONE);
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::accepted()
    {
      qDebug()<<"";
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
        t.setGroupByTimeInterval(_M_ui->group_timeinterval->currentIndex());
        t.taskFilter().setFilterType(_M_ui->task_filter_type->currentIndex());
        t.taskFilter().setSelection(_M_selected_tasks);
        t.projectFilter().setFilterType(_M_ui->project_filter_type->currentIndex());
        t.projectFilter().setSelection(_M_selected_projects);
        t.setExportDataFileTemplate(_M_ui->export_data_file->text());        
        context()->reportManager()->store(t);
      }
      accept();
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::rejected()
    {
      reject();
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::select_projects()
    {
      SelectProjectsDialog dlg;
      dlg.select(_M_selected_projects);
      if(dlg.exec()==QDialog::Accepted)
      {
        _M_selected_projects = dlg.selection();
      }
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::select_tasks()
    {
      SelectTasksDialog dlg;
      dlg.select(_M_selected_tasks);
      if(dlg.exec()==QDialog::Accepted)
      {
        _M_selected_tasks = dlg.selection();
      }
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::update_select_tasks_enabled_state(int selected_filter_type)
    {
      _M_ui->select_tasks->setEnabled(selected_filter_type != ReportDataFilterType::NO_FILTER);
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::update_select_projects_enabled_state(int selected_filter_type)
    {
      _M_ui->select_projects->setEnabled(selected_filter_type != ReportDataFilterType::NO_FILTER);
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::on_report_name_changed(QString const& name)
    {
      this->enableButtonOk(!name.isEmpty());
    }
    // ---------------------------------------------------------------------------------
    void EditReportTypeDialog::select_target_file()
    {
      QString path = _M_ui->export_data_file->text();
      QString const& selection = QFileDialog::getSaveFileName(this, i18n("Save File"), path);
      if(!selection.isEmpty())
      {
        _M_ui->export_data_file->setText(selection);
      }
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#include <editreporttypedialog.moc>
