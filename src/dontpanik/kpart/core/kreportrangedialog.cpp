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
#include "ui_kreportrangedialog.h"

#include <QStringList>

namespace dp
{
  namespace core
  {
    KReportRangeDialog::KReportRangeDialog ( QWidget* parent, Qt::WindowFlags f)
    :QDialog(parent, f)
    , _M_ui(new Ui::KReportRangeDialog())
    {
      _M_ui->setupUi(this);
      init_actions();
      init_presets();
      init_ui();
      
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
    }
    
    void KReportRangeDialog::on_use_preset_toggled(bool checked)
    {
      _M_ui->preset_choice->setEnabled(checked);
      _M_ui->custom_from->setDisabled(checked);
      _M_ui->custom_to->setDisabled(checked);
    }   
  }
}

