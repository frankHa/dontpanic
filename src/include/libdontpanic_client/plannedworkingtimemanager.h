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

#ifndef DP_CLIENT_PLANNEDWORKINGTIMEMANAGER_H
#define DP_CLIENT_PLANNEDWORKINGTIMEMANAGER_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/worktimeperday.h>
#include <libdontpanic_client/detail/cache.hpp>

class OrgDontpanicPlannedWorkingTimeManagerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicPlannedWorkingTimeManagerInterface PlannedWorkingTimeManager;
  }
}

namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    class DP_EXPORT PlannedWorkingTimeManager
          : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
        typedef detail::cache<WorktimePerDay, NullWorktimePerDay> cache_t;
        // ---------------------------------------------------------------------------------
      signals:
        // ---------------------------------------------------------------------------------
        void stored ( dp::WorktimePerDay );
        // ---------------------------------------------------------------------------------
        void removed ( dp::WorktimePerDay );
        // ---------------------------------------------------------------------------------
        void error ( QString );
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_stored ( dp::WorktimePerDay );
        // ---------------------------------------------------------------------------------
        void on_removed ( dp::WorktimePerDay );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        PlannedWorkingTimeManager ( QObject *parent = 0 );
        ~PlannedWorkingTimeManager ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void store ( WorktimePerDayList const& wl );
        // ---------------------------------------------------------------------------------
        void store ( WorktimePerDay const& p );
        // ---------------------------------------------------------------------------------
        void remove ( WorktimePerDay const& p );
        // ---------------------------------------------------------------------------------
        WorktimePerDay load ( int p );
        // ---------------------------------------------------------------------------------
        QTime plannedWorkHoursToday();
        // ---------------------------------------------------------------------------------
        WorktimePerDayList worktimesForWholeWeek();
        // ---------------------------------------------------------------------------------
        void storeCurrentHolidayRegion ( QString const& r );
        // ---------------------------------------------------------------------------------
        QString loadCurrentHolidayRegion();
        // ---------------------------------------------------------------------------------
        bool isWorkDay ( QDate const&day );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::PlannedWorkingTimeManager *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::PlannedWorkingTimeManager *_M_remote;
        // ---------------------------------------------------------------------------------
        cache_t _M_cache;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PLANNEDWORKINGTIMEMANAGER_H
