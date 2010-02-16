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
        ,_M_remote(0)
        , _M_current_action(NullAction()){}
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
    // ---------------------------------------------------------------------------------,
    void TimeTracker::startActionFromTemplate(Uuid const& t)
    {
      QDBusPendingReply<> reply =remote()->startNewActionFromTemplate(t);
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------,
    void TimeTracker::remove(Action const& a)
    {
      QDBusPendingReply<> reply =remote()->remove(a);
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    void TimeTracker::store(Action const& a)
    {
      QDBusPendingReply<> reply =remote()->store(a);
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
    void TimeTracker::continueLastAction()
    {
      QDBusPendingReply<> reply =remote()->continueLastAction();
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
      QDateTime _to(day, QTime(23, 59, 59, 99));
      return findAll(_from, _to);
    }
    // ---------------------------------------------------------------------------------      
    ActionList TimeTracker::findAll(QDate const& from, QDate const& to)
    {
      QDateTime _from(from);
      QDateTime _to(to, QTime(23, 59, 59, 99));
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
      _M_latest_actions = reply.value();
      return reply.value();
    }
    // ---------------------------------------------------------------------------------
    Action TimeTracker::currentlyActiveAction() const
    {
     if(_M_current_action.isActive())
     {
       return _M_current_action;
     }
     return NullAction();
    }    
    // ---------------------------------------------------------------------------------
    bool TimeTracker::hasActionsFor(QDate const& date)
    {
      QDBusPendingReply<bool> reply =remote()->hasActionsFor(date);
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
        connect(_M_remote, SIGNAL( stored ( dp::Action ) ), this, SLOT( on_stored ( dp::Action ) ));
        connect(_M_remote, SIGNAL(removed(dp::Action)), this, SLOT(on_removed(dp::Action)));
        connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
        setCurrentlyActiveAction(_M_remote->findCurrentlyActiveAction());
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------      
    void TimeTracker::on_stored(dp::Action const& a)
    {
      if(a.isActive() || a == _M_current_action) setCurrentlyActiveAction(a);
      emit stored(a);
    }
    // ---------------------------------------------------------------------------------      
    void TimeTracker::on_removed(dp::Action const& a)
    {
      if(a == _M_current_action) setCurrentlyActiveAction(NullAction());
      emit removed(a);
    }
    // ---------------------------------------------------------------------------------
    void TimeTracker::setCurrentlyActiveAction(dp::Action const& a)
    {
      _M_current_action = a;
      emit currentlyActiveActionChanged(a);
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

