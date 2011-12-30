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

#ifndef DP_CORE_KTIMERANGEDIALOG_H
#define DP_CORE_KTIMERANGEDIALOG_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/timerange.h>
#include <KDialog>

namespace Ui
{
  class KReportRangeDialog;
}

namespace dp
{
  class TimeRange;
  namespace core
  {
    class KReportRangeDialog 
    : public KDialog
    {
      Q_OBJECT
      
      enum Range{LAST_MONTH, THIS_MONTH, LAST_WEEK, THIS_WEEK, LAST_YEAR, THIS_YEAR, CUSTOM};
      public:
        KReportRangeDialog ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
        ~KReportRangeDialog();
        
      public:
        TimeRange selectedRange() const;
      private slots:
        void init_ui();
        void init_presets();
        void init_actions();
        
        void on_use_preset_toggled(bool);
        void on_preset_chosen(int);
        
        TimeRange custom_range() const;
        TimeRange last_month() const;
        TimeRange this_month() const;
        TimeRange last_week() const;
        TimeRange this_week() const;
        TimeRange last_year() const;
        TimeRange this_year() const;
        
      private:
        Ui::KReportRangeDialog *_M_ui;
        int _M_range;
    };
  }
}

#endif // DP_CORE_KTIMERANGEDIALOG_H
