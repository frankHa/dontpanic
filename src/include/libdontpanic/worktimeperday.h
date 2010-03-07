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
      friend QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::WorktimePerDay & wtpd );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      WorktimePerDay ( int day );
      // ---------------------------------------------------------------------------------
      // required by DBusArgument streaming operator:
      // ---------------------------------------------------------------------------------
      WorktimePerDay();
      // ---------------------------------------------------------------------------------
    protected:
      // ---------------------------------------------------------------------------------
      WorktimePerDay &setDay ( int );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      bool isValid() const;
      // ---------------------------------------------------------------------------------
      int day() const;
      // ---------------------------------------------------------------------------------
      WorktimePerDay &setPlannedWorkingHours ( QTime const& pwh );
      // ---------------------------------------------------------------------------------
      QTime plannedWorkingHours() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      int _M_day_of_week;
      // ---------------------------------------------------------------------------------
      QTime _M_time;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  typedef QList<WorktimePerDay> WorktimePerDayList;
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == ( dp::WorktimePerDay const& lhs, dp::WorktimePerDay const& rhs );
  // ---------------------------------------------------------------------------------
  class NullWorktimePerDay: public WorktimePerDay
  {
    public:
      NullWorktimePerDay() : WorktimePerDay() {}
  };
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_WORKTIMEPERDAY_H
