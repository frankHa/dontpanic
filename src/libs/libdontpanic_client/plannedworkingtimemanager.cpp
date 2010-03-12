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

#include "libdontpanic_client/plannedworkingtimemanager.h"
#include <QDBusConnection>
#include <libdontpanic/task.hpp>
#include <remote_planned_working_time_manager.h>

namespace dp
{
  namespace client
  {
    PlannedWorkingTimeManager::PlannedWorkingTimeManager ( QObject *parent )
        : QObject ( parent )
        , _M_remote ( 0 )
    {

    }
    // ---------------------------------------------------------------------------------
    PlannedWorkingTimeManager::~PlannedWorkingTimeManager ( ) {}
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::store ( WorktimePerDay const& p )
    {
      QDBusPendingReply<> reply = remote()->store ( p );
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::store ( WorktimePerDayList const& wl )
    {
      QDBusPendingReply<> reply = remote()->store ( wl );
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
    }
    // ---------------------------------------------------------------------------------
    WorktimePerDay PlannedWorkingTimeManager::load ( int id )
    {
      return _M_cache.load ( id, remote() );
    }
    // ---------------------------------------------------------------------------------
    QTime PlannedWorkingTimeManager::plannedWorkHoursToday()
    {
      QDate const& today = QDate::currentDate();
      if(!isWorkDay(today)){return QTime(0,0);}
      int day = today.dayOfWeek();
      return load ( day ).plannedWorkingHours();
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::remove ( WorktimePerDay const& p )
    {
      QDBusPendingReply<> reply = remote()->remove ( p );
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
    }
    // ---------------------------------------------------------------------------------
    WorktimePerDayList PlannedWorkingTimeManager::worktimesForWholeWeek()
    {
      return _M_cache.find_all ( remote() );
    }
    // ---------------------------------------------------------------------------------
    QString PlannedWorkingTimeManager::loadCurrentHolidayRegion()
    {
      QDBusPendingReply<QString> reply = remote()->loadCurrentHolidayRegion();
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
      return reply.value();
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::storeCurrentHolidayRegion(QString const& region)
    {
      QDBusPendingReply<> reply = remote()->storeCurrentHolidayRegion(region);
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
    }
    // ---------------------------------------------------------------------------------
    bool PlannedWorkingTimeManager::isWorkDay ( QDate const& day )
    {
      QDBusPendingReply<bool> reply = remote()->isWorkDay ( day );
      reply.waitForFinished();
      if ( reply.isError() )
      {
        kWarning() << reply.error();
        emit error ( QDBusError::errorString ( reply.error().type() ) );
      }
      return reply.value();
    }
    // ---------------------------------------------------------------------------------
    org::dontpanic::PlannedWorkingTimeManager* PlannedWorkingTimeManager::remote()
    {
      if ( _M_remote == 0 )
      {
        _M_remote = new org::dontpanic::PlannedWorkingTimeManager
        ( "org.dontpanic", "/PlannedWorkingTimeManager", QDBusConnection::sessionBus(), this );
        if ( !_M_remote->isValid() )
        {
          kWarning() << _M_remote->lastError();
        }
        connect ( _M_remote, SIGNAL ( stored ( dp::WorktimePerDay ) ), this, SLOT ( on_stored ( dp::WorktimePerDay ) ) );
        connect ( _M_remote, SIGNAL ( removed ( dp::WorktimePerDay ) ), this, SLOT ( on_removed ( dp::WorktimePerDay ) ) );
        connect ( _M_remote, SIGNAL ( error ( QString const& ) ), this, SIGNAL ( error ( QString ) ) );
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::on_stored ( dp::WorktimePerDay t )
    {
      _M_cache.store ( t );
      emit stored ( t );
    }
    // ---------------------------------------------------------------------------------
    void PlannedWorkingTimeManager::on_removed ( dp::WorktimePerDay t )
    {
      _M_cache.remove ( t );
      emit removed ( t );
    }
  }
}

