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

#include <libdontpanic/reportdatafilter.h>
#include <libdontpanic/reporttype.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ReportDataFilter::ReportDataFilter()
  : _M_type(ReportType::NO_FILTER){}
  // ---------------------------------------------------------------------------------
  int ReportDataFilter::filterType() const
  {
    return _M_type;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter& ReportDataFilter::setFilterType (int type)
  {
    _M_type = type;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter::Entries &
  ReportDataFilter::entries()
  {
    return _M_entries;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter::Entries const& 
  ReportDataFilter::entries() const
  {
    return _M_entries;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

