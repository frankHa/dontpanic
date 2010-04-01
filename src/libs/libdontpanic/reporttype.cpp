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

#include <libdontpanic/reporttype.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  ///ctor
  ReportType::ReportType()
      : _M_id ( Uuid::generate() )
      , _M_name ( "" )
      , _M_icon("")
      , _M_group_by_task(false)
      , _M_group_by_project(false)
      , _M_group_by_time_interval(NONE){}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( QString const& title )
      : _M_id ( Uuid::generate() )
      , _M_name ( title ) 
      , _M_icon("")
      , _M_group_by_task(false)
      , _M_group_by_project(false)
      , _M_group_by_time_interval(NONE){}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( Uuid const& id )
      : _M_id ( id )
      , _M_name ( "" ) 
      , _M_icon("")
      , _M_group_by_task(false)
      , _M_group_by_project(false)
      , _M_group_by_time_interval(NONE){}
  // ---------------------------------------------------------------------------------
  Uuid const& ReportType::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setName ( QString title )
  {
    _M_name = title;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::icon() const
  {
    return _M_icon;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setIcon ( QString icon )
  {
    _M_icon = icon;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setGroupByTask(bool b)
  {
    _M_group_by_task = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::groupByTask() const
  {
    return _M_group_by_task;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setGroupByProject(bool b)
  {
    _M_group_by_project = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::groupByProject() const
  {
    return _M_group_by_project;
  }
  // ---------------------------------------------------------------------------------
  int ReportType::groupByTimeInterval() const
  {
    return _M_group_by_time_interval;
  }
  // ---------------------------------------------------------------------------------
  ReportType & ReportType::setGroupByTimeInterval(int interval_type)
  {
    _M_group_by_time_interval = interval_type;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter & ReportType::taskFilter()
  {
    return _M_task_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter const& ReportType::taskFilter() const
  {
    return _M_task_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter & ReportType::projectFilter()
  {
    return _M_project_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter const& ReportType::projectFilter() const
  {
    return _M_project_filter;
  }
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::ReportType const& lhs, dp::ReportType const& rhs)
  {
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------