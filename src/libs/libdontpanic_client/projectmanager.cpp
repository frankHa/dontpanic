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
#include <remote_projectmanager.h>
#include <QDBusConnection>

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
      qDebug()<<__FUNCTION__;
      connect(remote(), SIGNAL(stored(dp::Project)), this, SLOT(onstored(dp::Project)));
      connect(remote(), SIGNAL(removed(dp::Project)), this, SLOT(onremoved(dp::Project)));
    }
    // ---------------------------------------------------------------------------------
    ProjectManager::~ProjectManager ( ){}
    // ---------------------------------------------------------------------------------
    void ProjectManager::store(Project const& p)
    {
      _M_remote->store(p);
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::remove(Project const& p)
    {
      _M_remote->remove(p);
    }
    // ---------------------------------------------------------------------------------
    ProjectList ProjectManager::allProjects()
    {
      return _M_remote->allProjects();
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::onstored(dp::Project p)
    {
      qDebug()<<__FUNCTION__;
      emit stored(p);
    }
    // ---------------------------------------------------------------------------------
    void ProjectManager::onremoved(dp::Project p)
    {
      qDebug()<<__FUNCTION__;
      emit removed(p);
    }
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
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

