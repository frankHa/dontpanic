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

#ifndef DP_CORE_KSTATUS_H
#define DP_CORE_KSTATUS_H
#include <libdontpanic/defines.hpp>
#include <QObject>
// ---------------------------------------------------------------------------------
class QTimer;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    class ActionsCache;
  }
  // ---------------------------------------------------------------------------------
  class Action;
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    class KStatus: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      signals:
        // ---------------------------------------------------------------------------------
        void todaysDurationChanged ( int duration );
        // ---------------------------------------------------------------------------------
        void currentlySelectedDaysDurationChanged ( int duration );
        // ---------------------------------------------------------------------------------
        void currentProjectChanged ( QString const& project_description );
        // ---------------------------------------------------------------------------------
        void iconChanged ( QString const& icon );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        KStatus ( QObject* parent = 0 );
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void updateAll();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        void init();
        // ---------------------------------------------------------------------------------
        void ensure_correct_timer_state();
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_active_action_changed ( dp::Action const& );
        // ---------------------------------------------------------------------------------
        void on_selected_day_changed ( QDate const& day );
        // ---------------------------------------------------------------------------------
        void update();
        // ---------------------------------------------------------------------------------
      protected:
        // ---------------------------------------------------------------------------------
        /**
        * Reimplemented from QObject
        **/
        void timerEvent ( QTimerEvent *event );
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        int _M_timer_id;
        // ---------------------------------------------------------------------------------
        client::ActionsCache *_M_todays_actions;
        // ---------------------------------------------------------------------------------
        client::ActionsCache *_M_actions_of_selected_day;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CORE_KSTATUS_H
