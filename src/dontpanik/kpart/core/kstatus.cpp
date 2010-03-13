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
#include <libdontpanic/time.hpp>
#include <QTimerEvent>

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
        , _M_cached_selected_day ( QDate::currentDate() )
        , _M_cached_todays_duration ( 0 )
        , _M_cached_selected_days_duration ( 0 )
        , _M_cached_icon ( "" )
        , _M_cached_project ( "" )
    {
      init();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateAll()
    {
      update();
      emit todaysDurationChanged ( _M_cached_todays_duration );
      emit currentlySelectedDaysDurationChanged ( _M_cached_selected_days_duration );
      emit currentProjectChanged ( _M_cached_project );
      emit iconChanged ( _M_cached_icon );
      
    }
    // ---------------------------------------------------------------------------------
    // protected stuff:
    // ---------------------------------------------------------------------------------
    void KStatus::timerEvent ( QTimerEvent* event )
    {
      if ( event->timerId() == _M_timer_id )
      {
        update();
      }
      QObject::timerEvent ( event );
    }

    // ---------------------------------------------------------------------------------
    //private stuff:
    // ---------------------------------------------------------------------------------
    void KStatus::init()
    {
      connect ( context()->timeTracker(), SIGNAL ( currentlyActiveActionChanged ( dp::Action ) ), this, SLOT ( on_active_action_changed ( dp::Action ) ) );
      connect ( context(), SIGNAL ( currentlySelectedDateChanged ( QDate const& ) ), this, SLOT ( on_selected_day_changed ( QDate const& ) ) );
      connect ( _M_todays_actions, SIGNAL ( stored ( dp::Action ) ), this, SLOT ( on_action_stored ( dp::Action ) ) );
      connect ( _M_todays_actions, SIGNAL ( removed ( dp::Action ) ), this, SLOT ( on_action_removed ( dp::Action ) ) );
      connect ( _M_actions_of_selected_day, SIGNAL ( stored ( dp::Action ) ), this, SLOT ( on_action_stored ( dp::Action ) ) );
      connect ( _M_actions_of_selected_day, SIGNAL ( removed ( dp::Action ) ), this, SLOT ( on_action_removed ( dp::Action ) ) );
      _M_todays_actions->setSourceTimeTracker ( context()->timeTracker() );
      _M_todays_actions->initCache ( QDate::currentDate() );
      _M_actions_of_selected_day->setSourceTimeTracker ( context()->timeTracker() );
      _M_actions_of_selected_day->initCache ( _M_cached_selected_day );
      
      update();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::ensure_correct_timer_state()
    {
      if ( context()->timeTracker()->currentlyActiveAction().isActive() )
      {
        if ( _M_timer_id == 0 )
        {
          _M_timer_id = startTimer ( 500 );
        }
      }
      else
      {
        if ( _M_timer_id  != 0 )
        {
          killTimer ( _M_timer_id );
          _M_timer_id = 0;
        }
      }
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_active_action_changed ( dp::Action const& ca )
    {
      ensure_correct_timer_state();
      QString description;
      if ( !ca.isActive() )
      {
        description = ( i18n ( "There is currently no running activity..." ) );
      }
      else
      {
        description = i18n ( "<html>Currently working on:<br/><b>%1 / %2</b><br/>since: <b>%3 (%4h)</b></html>" )
                      .arg ( context()->projectManager()->load ( ca.project() ).name() )
                      .arg ( context()->taskManager()->load ( ca.task() ).name() )
                      .arg ( ca.startTime().time().toString ( Qt::SystemLocaleShortDate ) )
                      .arg ( duration_formatter().format ( ca.duration() ) );
      }
      if ( _M_cached_project != description )
      {
        _M_cached_project = description;
        emit currentProjectChanged ( description );
      }
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_selected_day_changed ( QDate const& day )
    {
      if ( day == _M_cached_selected_day )
      {
        return;
      }
      _M_actions_of_selected_day->initCache ( day );
      _M_cached_selected_day = day;
      updateSelectedDaysDuration();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_action_stored ( Action const& a )
    {
      update();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::on_action_removed ( Action const& a )
    {
      update();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::update()
    {
      updateCurrentActivity();
      updateTodaysDuration();
      updateSelectedDaysDuration();
      updateIcon();
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateCurrentActivity()
    {
      on_active_action_changed ( context()->timeTracker()->currentlyActiveAction() );
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateTodaysDuration()
    {
      int current_duration = _M_todays_actions->duration();
      if ( _M_cached_todays_duration == current_duration )
      {
        return;
      }
      _M_cached_todays_duration = current_duration;
      emit todaysDurationChanged ( current_duration );
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateSelectedDaysDuration()
    {
      int current_duration = _M_actions_of_selected_day->duration();
      if ( _M_cached_selected_days_duration == current_duration )
      {
        return;
      }
      _M_cached_selected_days_duration = current_duration;
      emit currentlySelectedDaysDurationChanged ( current_duration );
    }
    // ---------------------------------------------------------------------------------
    void KStatus::updateIcon()
    {
      updateTodaysDuration();
      QString icon;
      if ( context()->timeTracker()->currentlyActiveAction().isActive() )
      {
        if ( _M_cached_todays_duration < dp::time::minutes ( context()->plannedWorkingtimeManager()->plannedWorkHoursToday() ) )
        {
          icon =  "dontpanik-green";
        }
        else
        {
          icon = "dontpanik-red";
        }
      }
      else
      {
        icon = "dontpanik";
      }
      if ( icon == _M_cached_icon )
      {
        return;
      }
      _M_cached_icon = icon;
      emit iconChanged ( _M_cached_icon );
    }
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
