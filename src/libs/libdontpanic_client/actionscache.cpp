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

#include <libdontpanic_client/actionscache.h>
#include <libdontpanic_client/timetracker.h>

namespace dp
{
  namespace client
  {
    // ---------------------------------------------------------------------------------
    ActionsCache::ActionsCache ( QObject *parent )
        : QObject ( parent )
        , _M_source ( 0 )
        , _M_is_live_cache ( false ) {}
    // ---------------------------------------------------------------------------------
    ActionsCache& ActionsCache::setSourceTimeTracker ( TimeTracker *source )
    {
      _M_source = source;
      connect ( _M_source, SIGNAL ( stored ( dp::Action ) ), this, SLOT ( on_action_stored ( dp::Action const& ) ) );
      connect ( _M_source, SIGNAL ( removed ( dp::Action ) ), this, SLOT ( on_action_removed ( dp::Action const& ) ) );
      return *this;
    }
    // ---------------------------------------------------------------------------------
    ActionsCache& ActionsCache::initCache ( TimeRange const& timerange )
    {
      Q_ASSERT ( _M_source );
      _M_current_time_range = timerange;
      _M_actions = _M_source->findAll ( timerange.from(), timerange.to() );
      _M_is_live_cache = false;
      return *this;
    }
    // ---------------------------------------------------------------------------------
    ActionsCache& ActionsCache::initCache()
    {
      initCache ( QDate() );
      _M_is_live_cache = true;
      return *this;
    }
    // ---------------------------------------------------------------------------------
    ActionsCache& ActionsCache::initCache ( QDate const& date )
    {
      _M_is_live_cache = false;
      QDateTime _from ( date );
      QDateTime _to ( date, QTime ( 23, 59, 59, 99 ) );
      return initCache ( TimeRange ( _from, _to ) );
    }
    // ---------------------------------------------------------------------------------
    int ActionsCache::duration() const
    {
      return _M_actions.duration();
    }
    // ---------------------------------------------------------------------------------
    ActionList ActionsCache::cachedActions() const
    {
      return _M_actions;
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void ActionsCache::on_action_stored ( dp::Action a )
    {
      if ( is_already_known ( a ) )
      {
        updated ( a );
      }
      else
      {
        added ( a );
      }
    }
    // ---------------------------------------------------------------------------------
    void ActionsCache::on_action_removed ( dp::Action a )
    {
      int i = _M_actions.indexOf ( a );
      _M_actions.removeAt ( i );
      emit removed ( a );
    }
    // ---------------------------------------------------------------------------------
    bool ActionsCache::is_already_known ( dp::Action const&a ) const
    {
      return ( _M_actions.indexOf ( a ) != -1 );
    }
    // ---------------------------------------------------------------------------------
    void ActionsCache::added ( dp::Action const&a )
    {
      update_timerange_if_necessary();
      if ( !is_interesting_for_current_timerange ( a ) )
      {
        return;
      }
      _M_actions.append ( a );
      emit stored ( a );
    }
    // ---------------------------------------------------------------------------------
    void ActionsCache::updated ( dp::Action const&a )
    {
      if ( !is_interesting_for_current_timerange ( a ) )
      {
        on_action_removed ( a );
        return;
      }
      int row = _M_actions.indexOf ( a );
      _M_actions.replace ( row, a );
      emit stored ( a );
    }
    // ---------------------------------------------------------------------------------
    bool ActionsCache::is_interesting_for_current_timerange ( dp::Action const&a )
    {
      if ( !_M_current_time_range.isValid() )
      {
        return false;
      }
      bool result = ( a.startTime() >= _M_current_time_range.from() && a.startTime() <= _M_current_time_range.to() );
      return result;
    }
    // ---------------------------------------------------------------------------------
    void ActionsCache::update_timerange_if_necessary()
    {
      if(not _M_is_live_cache){return;}
      QDate now;
      if(now>_M_current_time_range.to().date())
      {
        initCache();
      }
    }
    // ---------------------------------------------------------------------------------
  }
}

