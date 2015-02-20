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

#include "plannedworkingtimesdialog.h"
#include "ui_plannedworkingtimesdialog.h"
#include <libdontpanic/worktimeperday.h>
#include "context.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    PlannedWorkingTimesDialog::PlannedWorkingTimesDialog ( QWidget* parent, Qt::WindowFlags f )
        : QDialog ( parent, f )
        , _M_ui ( new Ui::PlannedWorkingTimesDialog )
    {
      _M_ui->setupUi ( this );
      setWindowTitle(i18n("Planned Working Times"));
      init_planned_working_hours_per_day();
      init_holiday_region();
      setup_actions();
      _M_ui->gb_holidays->setVisible(false);
    }
    // ---------------------------------------------------------------------------------
    PlannedWorkingTimesDialog::~PlannedWorkingTimesDialog()
    {
      delete _M_ui;
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::init_planned_working_hours_per_day()
    {
      _M_time_edit_list
      << _M_ui->monday
      << _M_ui->tuesday
      << _M_ui->wednesday
      << _M_ui->thursday
      << _M_ui->friday
      << _M_ui->saturday
      << _M_ui->sunday;
      init_time_values();
      connect ( this, SIGNAL ( accepted() ), this, SLOT ( store() ) );
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::init_holiday_region()
    {
      //_M_ui->holiday_region->selectRegion ( context()->plannedWorkingtimeManager()->loadCurrentHolidayRegion() );
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::init_time_values()
    {
      dp::client::PlannedWorkingTimeManager *time_manager = context()->plannedWorkingtimeManager();
      for ( int i = 0; i < _M_time_edit_list.size(); ++i )
      {
        int day = i + 1;
        WorktimePerDay const& wtpd = time_manager->load ( day );
        QTime  const& t = wtpd.plannedWorkingHours();
        if ( wtpd.isValid() )
        {
          _M_time_edit_list[i]->setTime ( t );
        }
      }
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::store()
    {
      store_time_values();
      store_holiday_region();
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::setup_actions()
    {
      connect(_M_ui->buttons, SIGNAL(accepted()), this, SLOT(accept()));
      connect(_M_ui->buttons, SIGNAL(rejected()), this, SLOT(reject()));
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::store_time_values()
    {
      dp::client::PlannedWorkingTimeManager *time_manager = context()->plannedWorkingtimeManager();
      WorktimePerDayList wtpds;
      for ( int i = 0; i < _M_time_edit_list.size(); ++i )
      {
        int day = i + 1;
        WorktimePerDay wtpd ( day );
        wtpd.setPlannedWorkingHours ( _M_time_edit_list[i]->time () );
        wtpds << wtpd;
      }
      time_manager->store ( wtpds );
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimesDialog::store_holiday_region()
    {
      //context()->plannedWorkingtimeManager()->storeCurrentHolidayRegion(_M_ui->holiday_region->selectedRegion());
    }

    // ---------------------------------------------------------------------------------
  }//core
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

