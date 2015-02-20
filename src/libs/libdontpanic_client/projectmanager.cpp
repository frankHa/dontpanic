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

#include "libdontpanic_client/projectmanager.h"
#include <QDBusConnection>
#include <libdontpanic/project.hpp>
#include <remote_projectmanager.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    ProjectManager::ProjectManager ( QObject *parent )
        : QObject ( parent )
        ,_M_remote(0)
    {
    }
    // ---------------------------------------------------------------------------------
    ProjectManager::~ProjectManager ( ){}
    // ---------------------------------------------------------------------------------
    void ProjectManager::store(Project const& p)
    {
      QDBusPendingReply<> reply =remote()->store(p);
      reply.waitForFinished();
      if(reply.isError())
      {
        qWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    Project ProjectManager::load(Uuid const& id)
    {
      return _M_cache.load(id, remote());      
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::remove(Project const& p)
    {
      QDBusPendingReply<> reply =remote()->remove(p);
      reply.waitForFinished();
      if(reply.isError())
      {
      qWarning()<<reply.error();
      emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    ProjectList ProjectManager::allProjects()
    {
      return _M_cache.find_all(remote());
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    org::dontpanic::ProjectManager* ProjectManager::remote()
    {
      if(_M_remote == 0)
      {
      _M_remote = new org::dontpanic::ProjectManager
      ( "org.dontpanic", "/ProjectManager", QDBusConnection::sessionBus(), this );
      if(!_M_remote->isValid())
      {
        qWarning()<<_M_remote->lastError();
      }
      connect(_M_remote, SIGNAL( stored ( dp::Project ) ), this, SLOT( on_stored ( dp::Project ) ));
      connect(_M_remote, SIGNAL(removed(dp::Project)), this, SLOT(on_removed(dp::Project)));
      connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::on_stored(dp::Project p)
    {
      _M_cache.store(p);
      emit stored(p);
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::on_removed(dp::Project p)
    {
      _M_cache.remove(p);
      emit removed(p);
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

