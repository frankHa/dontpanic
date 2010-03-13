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

#ifndef CP_CLIENT_ACTIONSCACHE_H
#define CP_CLIENT_ACTIONSCACHE_H

#include <QObject>
#include <libdontpanic/defines.hpp>
#include <libdontpanic/action.hpp>
#include <libdontpanic/timerange.h>

class QDate;

namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    class TimeTracker;
    class ActionsCache : public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        ActionsCache ( QObject *parent = 0 );
        // ---------------------------------------------------------------------------------
      signals:
        // ---------------------------------------------------------------------------------
        void stored ( dp::Action );
        // ---------------------------------------------------------------------------------
        void removed ( dp::Action );
        // ---------------------------------------------------------------------------------
        void timerangeChanged();
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        ActionsCache& setSourceTimeTracker ( TimeTracker *source );
        // ---------------------------------------------------------------------------------
        ActionsCache& initCache ( TimeRange const& timerange );
        // ---------------------------------------------------------------------------------
        ActionsCache& initCache ( QDate const& date );
        // ---------------------------------------------------------------------------------
        int duration() const;
        // ---------------------------------------------------------------------------------
        ActionList cachedActions() const;
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_action_stored ( dp::Action );
        // ---------------------------------------------------------------------------------
        void on_action_removed ( dp::Action );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        bool is_already_known ( dp::Action const& ) const;
        // ---------------------------------------------------------------------------------
        void added ( dp::Action const& );
        // ---------------------------------------------------------------------------------
        void updated ( dp::Action const& );
        // ---------------------------------------------------------------------------------
        bool is_interesting_for_current_timerange ( dp::Action const& );
        // ---------------------------------------------------------------------------------

      private:
        // ---------------------------------------------------------------------------------
        TimeTracker *_M_source;
        // ---------------------------------------------------------------------------------
        ActionList _M_actions;
        // ---------------------------------------------------------------------------------
        TimeRange _M_current_time_range;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // CP_CLIENT_ACTIONSCACHE_H
