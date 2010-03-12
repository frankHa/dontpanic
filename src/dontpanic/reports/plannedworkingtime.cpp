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
// ---------------------------------------------------------------------------------
#include "plannedworkingtime.h"
#include <libdontpanic/time.hpp>
#include <libdontpanic/timerange.h>
#include <libdontpanic/worktimeperday.h>
#include <context.h>
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    // ---------------------------------------------------------------------------------
    namespace detail
    {
      typedef QMap<Qt::DayOfWeek, QTime> work_time_per_day_map;

      work_time_per_day_map planned_times()
      {
        work_time_per_day_map work_time_per_day;
        WorktimePerDayList wtpdl;
        persistence().findAll ( wtpdl );
        foreach ( WorktimePerDay const& wtpd, wtpdl )
        {
          if ( wtpd.isValid() )
          {
            work_time_per_day[ ( Qt::DayOfWeek ) wtpd.day() ] = wtpd.plannedWorkingHours();
          }
        }
        return work_time_per_day;
      }
      // ---------------------------------------------------------------------------------
      Qt::DayOfWeek current_day ( int first, long offset )
      {
        Qt::DayOfWeek result = ( Qt::DayOfWeek ) ( ( ( ( first - 1 ) + offset ) % 7 ) + 1 );
        return result;
      }
    }
    // ---------------------------------------------------------------------------------
    long planned_working_time_for ( TimeRange const& range )
    {
      if ( !range.isValid() )
      {
        return 0;
      }
      QDate const& from = range.from().date();
      QDate const& to = range.to().date();
      detail::work_time_per_day_map wtpdm = detail::planned_times();
      long result = 0;
      for ( QDate date = from; date <= to; date=date.addDays ( 1 ) )
      {
        if(is_work_day(date))
        {
          result += dp::time::minutes ( wtpdm[ ( Qt::DayOfWeek ) date.dayOfWeek() ] );
        }
      }
      return result;

    }
    // ---------------------------------------------------------------------------------
    bool is_work_day ( const QDate& day )
    {
      context()->plannedWorkingtimeManager()->isWorkDay(day);
    }

    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}

