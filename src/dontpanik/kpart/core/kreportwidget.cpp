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

#include "kreportwidget.h"
#include "ui_kreportwidget.h"
#include "context.h"
#include <libdontpanic/durationformatter.h>
#include <libdontpanic/timerangeformatter.h>
#include <QPropertyAnimation>

namespace dp
{
  namespace core
  {
    KReportWidget::KReportWidget( QWidget* parent, Qt::WindowFlags f)
    :QWidget(parent, f)
    , _M_ui(new Ui::KReportWidget())
    {
      _M_ui->setupUi(this);
      _M_summary_animation = new QPropertyAnimation(_M_ui->summary, "maximumHeight", this);
      resetReport();
      subscribe_to_report_manager_signals();
    }
    
    KReportWidget::~KReportWidget()
    {
      delete _M_ui;
    }
    
    void KReportWidget::setReport(Report const& r)
    {
      _M_ui->report_type->setText(r.reportType().name());
      _M_ui->report_table->setReport(r);
      _M_ui->report_range->setText(time_range_formatter().pretty_ui_format ( r.range() ));
      _M_ui->duration->setText(duration_formatter().format(r.duration()));
      _M_ui->planned_time->setText(duration_formatter().format(r.plannedWorkingTime()));
      _M_ui->overtime->setText(duration_formatter().format(r.duration()-r.plannedWorkingTime()));
      setSummaryVisible(true);
    }
    
    void KReportWidget::resetReport()
    {
      setSummaryVisible(false);
      _M_ui->report_type->setText("");
      _M_ui->report_table->resetReport();
      _M_ui->report_range->setText("");
      _M_ui->duration->setText("");
      _M_ui->planned_time->setText("");
      _M_ui->overtime->setText("");
    }
    
    // private stuff:
    
    void KReportWidget::subscribe_to_report_manager_signals()
    {
      connect(context()->reportManager(), SIGNAL(generated(Report)), this, SLOT(setReport(Report)));
    }
    
    void KReportWidget::setSummaryVisible(bool v)
    {
      int start =_M_ui->summary->maximumHeight();
      int target;
      if(v)
      {
        start = 0;
        target = _M_ui->summary->sizeHint().height();
      }
      else
      {
        target = 0;
      }
      _M_summary_animation->setDuration(500);
      _M_summary_animation->setStartValue(start);
      _M_summary_animation->setEndValue(target);
      if(!this->isVisible()){_M_ui->summary->setMaximumHeight(target); return;}
      _M_summary_animation->start();
    }
    
    
  }
}

