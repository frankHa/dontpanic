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

#ifndef DP_CORE_PLANNEDWORKINGTIMESDIALOG_H
#define DP_CORE_PLANNEDWORKINGTIMESDIALOG_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
// ---------------------------------------------------------------------------------
#include <QDialog>
// ---------------------------------------------------------------------------------
class QTimeEdit;
// ---------------------------------------------------------------------------------
namespace Ui
{
  class PlannedWorkingTimesDialog;
}
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class PlannedWorkingTimesDialog
          : public QDialog
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        PlannedWorkingTimesDialog ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        // ---------------------------------------------------------------------------------
        ~PlannedWorkingTimesDialog();
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void store();
        // ---------------------------------------------------------------------------------
        void init_time_values();
        // ---------------------------------------------------------------------------------
        void store_time_values();
        // ---------------------------------------------------------------------------------
        void store_holiday_region();
        // ---------------------------------------------------------------------------------        
      private:
        // ---------------------------------------------------------------------------------
        void init_planned_working_hours_per_day();
        // ---------------------------------------------------------------------------------
        void init_holiday_region();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        Ui::PlannedWorkingTimesDialog *_M_ui;
        // ---------------------------------------------------------------------------------
        QList<QTimeEdit*> _M_time_edit_list;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_PLANNEDWORKINGTIMESDIALOG_H
