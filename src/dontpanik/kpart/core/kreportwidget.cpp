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

namespace dp
{
  namespace core
  {
    KReportWidget::KReportWidget( QWidget* parent, Qt::WindowFlags f)
    :QWidget(parent, f)
    , _M_ui(new Ui::KReportWidget())
    {
      _M_ui->setupUi(this);
      subscribe_to_report_manager_signals();
    }
    
    KReportWidget::~KReportWidget()
    {
    }
    
    void KReportWidget::setReport(Report const& r)
    {
      _M_ui->report_type->setText(r.reportType());
      _M_ui->report->setText(r.reportData());
    }
    
    // private stuff:
    
    void KReportWidget::subscribe_to_report_manager_signals()
    {
      connect(context()->reportManager(), SIGNAL(generated(Report)), this, SLOT(setReport(Report)));
    }
  }
}

