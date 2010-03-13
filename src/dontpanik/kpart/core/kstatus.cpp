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

#include "kstatus.h"
#include "context.h"
#include <libdontpanic_client/actionscache.h>
#include <libdontpanic/durationformatter.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    KStatus::KStatus ( QObject* parent )
        : QObject ( parent )
        , _M_timer_id ( 0 )
        , _M_todays_actions ( new client::ActionsCache ( this ) )
        , _M_actions_of_selected_day ( new client::ActionsCache ( this ) )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateAll()
    {
      update();
    }
    // ---------------------------------------------------------------------------------
    // protected stuff:
    // ---------------------------------------------------------------------------------
    void KStatus::timerEvent ( QTimerEvent* event )
    {
      QObject::timerEvent ( event );
    }

    // ---------------------------------------------------------------------------------
    //private stuff:
    // ---------------------------------------------------------------------------------
    void KStatus::init()
    {

    }
    // ---------------------------------------------------------------------------------
    void KStatus::ensure_correct_timer_state()
    {
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_active_action_changed ( dp::Action const& ca)
    {
      if(!ca.isActive())
      {
        emit currentProjectChanged(i18n("There is currently no running activity..."));
      } 
      else
      {
        QString tooltip = i18n("Current Don't Panik action: \nProject:\t\t%1\nTask:\t\t%2\nRunning since:\t%3\nCurrent duration:\t%4")
        .arg(context()->projectManager()->load(ca.project()).name())
        .arg(context()->taskManager()->load(ca.task()).name())
        .arg(ca.startTime().time().toString(Qt::SystemLocaleShortDate))
        .arg(duration_formatter().format(ca.duration()));
        emit currentProjectChanged(tooltip);
      }
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_selected_day_changed ( QDate const& day )
    {
    }
    // ---------------------------------------------------------------------------------
    void KStatus::update()
    {
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
