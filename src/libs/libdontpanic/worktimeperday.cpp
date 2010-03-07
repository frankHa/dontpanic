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

#include <libdontpanic/worktimeperday.h>

namespace dp
{
  // ---------------------------------------------------------------------------------
  WorktimePerDay::WorktimePerDay ( int day )
  :_M_day_of_week(day)
  , _M_time(0,0)
  {}
  // ---------------------------------------------------------------------------------
  WorktimePerDay::WorktimePerDay()
  :_M_day_of_week(0)
  , _M_time(0,0)
  {}
  // ---------------------------------------------------------------------------------
  WorktimePerDay &WorktimePerDay::setDay ( int day)
  {
    _M_day_of_week = day;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  int WorktimePerDay::day() const
  {
    return _M_day_of_week;
  }
  // ---------------------------------------------------------------------------------
  WorktimePerDay &WorktimePerDay::setPlannedWorkingHours ( QTime const& pwh )
  {
    _M_time = pwh;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QTime WorktimePerDay::plannedWorkingHours() const
  {
    return _M_time;
  }
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == ( dp::WorktimePerDay const& lhs, dp::WorktimePerDay const& rhs )
  {
    return lhs.day() == rhs.day();
  }
  // ---------------------------------------------------------------------------------
}

