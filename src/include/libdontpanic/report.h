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

#ifndef DP_REPORT_H
#define DP_REPORT_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/timerange.h>
#include <libdontpanic/reporttype.h>
#include <libdontpanic/reportdata.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  class Report;
}
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::Report )
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT Report
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Report();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Report& setValid ( bool );
      // ---------------------------------------------------------------------------------
      bool isValid() const;
      // ---------------------------------------------------------------------------------
      Report & setReportType ( ReportType const& );
      // ---------------------------------------------------------------------------------
      ReportType reportType() const;
      // ---------------------------------------------------------------------------------
      Report & setRange ( TimeRange const& );
      // ---------------------------------------------------------------------------------
      TimeRange range() const;
      // ---------------------------------------------------------------------------------
      Report& setReportData ( ReportData const& data );
      // ---------------------------------------------------------------------------------
      ReportData reportData() const;
      // ---------------------------------------------------------------------------------
      Report& setDuration ( int duration );
      // ---------------------------------------------------------------------------------
      int duration() const;
      // ---------------------------------------------------------------------------------
      Report& setPlannedWorkingTime ( int planned_working_time );
      // ---------------------------------------------------------------------------------
      int plannedWorkingTime() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      bool      _M_valid;
      ReportType   _M_type;
      TimeRange _M_time_range;
      ReportData _M_report_data;
      int       _M_duration;
      int       _M_planned_working_time;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  inline Report report()
  {
    return Report();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_REPORT_H
