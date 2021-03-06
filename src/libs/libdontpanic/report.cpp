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

#include <libdontpanic/report.h>

namespace dp
{
  // ---------------------------------------------------------------------------------
  Report::Report()
      : _M_valid ( true )
      , _M_type ( NullReportType() )
      , _M_duration ( 0 )
      , _M_planned_working_time ( 0 ) {}
      // ---------------------------------------------------------------------------------
  Report & Report::setValid ( bool b )
  {
    _M_valid = b;
    return *this;
  } 
  // ---------------------------------------------------------------------------------
  bool Report::isValid() const  
  {
    return _M_valid;
  }
  // ---------------------------------------------------------------------------------
  Report & Report::setReportType ( ReportType const& t )
  {
    _M_type = t;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportType Report::reportType() const
  {
    return _M_type;
  }
  // ---------------------------------------------------------------------------------
  Report & Report::setRange ( TimeRange const& range )
  {
    _M_time_range = range;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  TimeRange Report::range() const
  {
    return _M_time_range;
  }
  // ---------------------------------------------------------------------------------
  Report& Report::setReportData ( ReportData const& data )
  {
    _M_report_data = data;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportData Report::reportData() const
  {
    return _M_report_data;
  }
  // ---------------------------------------------------------------------------------
  Report& Report::setDuration ( int d )
  {
    _M_duration = d;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  int Report::duration() const  
  {
    return _M_duration;
  }
  // ---------------------------------------------------------------------------------
  Report& Report::setPlannedWorkingTime ( int planned_working_time )
  {
    _M_planned_working_time = planned_working_time;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  int Report::plannedWorkingTime() const
  {
    return _M_planned_working_time;
  }
  // ---------------------------------------------------------------------------------
}

