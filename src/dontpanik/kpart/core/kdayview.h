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

#ifndef DP_KDAYVIEW_H
#define DP_KDAYVIEW_H
#include <libdontpanic/defines.hpp>
#include "dayinfo.h"

#include <QtWidgets/QWidget>
#include <QDate>
// ---------------------------------------------------------------------------------
namespace Ui
{
  class KDayView;
}
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class KDayView : public QWidget
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KDayView ( QWidget *parent );
        // ---------------------------------------------------------------------------------
        ~KDayView();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        DayInfo currentDay() const;
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void setup_actions();
        // ---------------------------------------------------------------------------------
        void save_actions_table_geometry();
        // ---------------------------------------------------------------------------------
        void restore_actions_table_geometry();
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_today_pressed();
        // ---------------------------------------------------------------------------------
        void on_selected_day_changed();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        Ui::KDayView *_M_ui;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_KDAYVIEW_H
