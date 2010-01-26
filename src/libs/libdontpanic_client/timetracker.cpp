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

#include "libdontpanic_client/timetracker.h"
#include <libdontpanic/actiontemplate.hpp>
#include <QDBusConnection>
#include <KDebug>
#include <remote_timetracker.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    TimeTracker::TimeTracker ( QObject *parent )
        : QObject ( parent )
        ,_M_remote(0) {}
    // ---------------------------------------------------------------------------------
    TimeTracker::~TimeTracker ( ){}
    // ---------------------------------------------------------------------------------
    void TimeTracker::startActionFromTemplate(ActionTemplate const& t)
    {
      QDBusPendingReply<> reply =remote()->startNewActionFromTemplate(t);
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    void TimeTracker::startNewAction()
    {
      QDBusPendingReply<> reply =remote()->startNewAction();
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    void TimeTracker::stopCurrentAction()
    {
      QDBusPendingReply<> reply =remote()->stopCurrentAction();
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    ActionList TimeTracker::findAll(QDate const& day)
    {
      QDateTime _from(day);
      QDateTime _to(_from.addDays(1));
      return findAll(_from, _to);
    }
    // ---------------------------------------------------------------------------------      
    ActionList TimeTracker::findAll(QDate const& from, QDate const& to)
    {
      QDateTime _from(from);
      QDateTime _to(from);
      return findAll(_from, _to);
    }
    // ---------------------------------------------------------------------------------
    ActionList TimeTracker::findAll(QDateTime const& from, QDateTime const& to)
    {
      QDBusPendingReply<ActionList> reply =remote()->findAll(from, to);
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
      return reply.value();
    }
    // ---------------------------------------------------------------------------------
    org::dontpanic::TimeTracker* TimeTracker::remote()
    {
      if(_M_remote == 0)
      {
        _M_remote = new org::dontpanic::TimeTracker
        ( "org.dontpanic", "/TimeTracker", QDBusConnection::sessionBus(), this );
        if(!_M_remote->isValid())
        {
          qWarning()<<_M_remote->lastError();
        }
        connect(_M_remote, SIGNAL( stored ( dp::Action ) ), this, SIGNAL( stored ( dp::Action ) ));
        connect(_M_remote, SIGNAL(removed(dp::Action)), this, SIGNAL(removed(dp::Action)));
        connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

