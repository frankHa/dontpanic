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

#include "kreportrangedialog.h"
#include <libdontpanic/timerange.h>
#include "ui_kreportrangedialog.h"

#include <QStringList>

namespace dp
{
  
  namespace core
  {
    KReportRangeDialog::KReportRangeDialog ( QWidget* parent, Qt::WindowFlags f)
    :QDialog(parent, f)
    , _M_ui(new Ui::KReportRangeDialog())
    , _M_range(LAST_MONTH)
    {
      _M_ui->setupUi(this);
      init_actions();
      init_presets();
      init_ui();
      
    }
    
    TimeRange KReportRangeDialog::selectedRange() const
    {
      switch(_M_range)
      {
        case LAST_MONTH: return last_month();        
        case THIS_MONTH: return this_month();
        case LAST_WEEK:  return last_week();
        case THIS_WEEK:  return this_week();
        case CUSTOM:
        default: return custom_range();
      }
    }
    
    KReportRangeDialog::~KReportRangeDialog()
    {
      delete _M_ui;
    }
    
    void KReportRangeDialog::init_presets()
    {
      QStringList presets;
      presets<<i18n("Last Month")
      <<i18n("This Month")
      <<i18n("Last Week")
      <<i18n("This Week");
      _M_ui->preset_choice->addItems(presets);
    }
    
    void KReportRangeDialog::init_ui()
    {
      _M_ui->preset_range->setChecked(true);
      on_use_preset_toggled(true);
      _M_ui->custom_from->setDate(QDate::currentDate());
      _M_ui->custom_to->setDate(QDate::currentDate());
    }
    
    void KReportRangeDialog::init_actions()
    {
      connect(_M_ui->preset_range, SIGNAL(toggled(bool)), this, SLOT(on_use_preset_toggled(bool)));
      connect(_M_ui->preset_choice, SIGNAL(currentIndexChanged(int)), this, SLOT(on_preset_chosen(int)));
    }
    
    TimeRange KReportRangeDialog::custom_range() const
    {
      return TimeRange(_M_ui->custom_from->dateTime(), _M_ui->custom_to->dateTime());
    }
    
    TimeRange KReportRangeDialog::last_month() const
    {
      QDate current = QDate::currentDate();
      QDate end(current.year(), current.month(), 1);
      QDate begin(end.addMonths(-1));
      return TimeRange(QDateTime(begin), QDateTime(end));
    }
    
    TimeRange KReportRangeDialog::this_month() const
    {
      QDate current = QDate::currentDate();
      QDate begin(current.year(), current.month(), 1);
      return TimeRange(QDateTime(begin), QDateTime(current));
    }
    
    TimeRange KReportRangeDialog::last_week() const
    {
      QDate current = QDate::currentDate();
      QDate end(current.addDays(-current.dayOfWeek()));
      QDate begin(end.addDays(-7));
      return TimeRange(QDateTime(begin), QDateTime(end));
    }
    
    TimeRange KReportRangeDialog::this_week() const
    {
      QDate end(QDate::currentDate());
      QDate begin(end.addDays(-end.dayOfWeek()));
      return TimeRange(QDateTime(begin), QDateTime(end));
    }
    
    void KReportRangeDialog::on_use_preset_toggled(bool checked)
    {
      _M_ui->preset_choice->setEnabled(checked);
      _M_ui->custom_from->setDisabled(checked);
      _M_ui->custom_to->setDisabled(checked);
      if(checked)
      {
        _M_range = _M_ui->preset_choice->currentIndex();
      } 
      else
      {
        _M_range = CUSTOM;
      }
    }  
    
    void KReportRangeDialog::on_preset_chosen(int index)
    {
      _M_range = index;
    }
  }
}

