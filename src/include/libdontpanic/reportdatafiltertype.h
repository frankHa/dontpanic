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

#ifndef DP_REPORTDATAFILTERTYPE_H
#define DP_REPORTDATAFILTERTYPE_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/enum.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class DP_EXPORT ReportDataFilterType
        : public Enum<ReportDataFilterType>
  {
    // ---------------------------------------------------------------------------------
    typedef dp::Enum<ReportDataFilterType> base;
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      enum value{NO_FILTER, SELECTED_ONLY, UNSELECTED_ONLY, INVALID=-1};
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      ReportDataFilterType(value v):base(v){}
      // ---------------------------------------------------------------------------------      
      static QStringList values();
      static QStringList pretty_names();
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_REPORTDATAFILTERTYPE_H
