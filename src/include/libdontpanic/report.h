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

namespace dp
{
  class Report
  {
    public:
      Report();
    public:
      Report& setValid(bool);
      bool isValid()const;      
      Report & setReportType(QString const&);
      QString reportType()const;
      Report & setRange(TimeRange const&);
      TimeRange range()const;
      Report& setReportData(QString const& data);
      QString reportData() const;
      
    private:
      bool      _M_valid;
      QString   _M_type;
      TimeRange _M_time_range;
      QString   _M_report_data;
  };
  
  inline Report report()
  {
    return Report();
  }
}

#endif // DP_REPORT_H
