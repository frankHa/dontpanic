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

#ifndef DP_WORKTIMEPERDAY_H
#define DP_WORKTIMEPERDAY_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
// ---------------------------------------------------------------------------------
#include <QTime>
// ---------------------------------------------------------------------------------
class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class WorktimePerDay
  {
    // ---------------------------------------------------------------------------------
    friend QDBusArgument const& operator >> ( QDBusArgument const&arg, WorktimePerDay & wtpd );
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      WorktimePerDay(Qt::DayOfWeek day);
      // ---------------------------------------------------------------------------------
    protected: 
      // ---------------------------------------------------------------------------------
      // required by DBusArgument streaming operator:
      // ---------------------------------------------------------------------------------
      WorktimePerDay();
      // ---------------------------------------------------------------------------------
      WorktimePerDay &setDay(Qt::DayOfWeek);
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Qt::DayOfWeek day() const;
      // ---------------------------------------------------------------------------------
      WorktimePerDay &setPlannedWorkingHours(QTime const& pwh);
      // ---------------------------------------------------------------------------------
      QTime plannedWorkingHours() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Qt::DayOfWeek _M_day_of_week;
      // ---------------------------------------------------------------------------------
      QTime _M_time;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_WORKTIMEPERDAY_H
