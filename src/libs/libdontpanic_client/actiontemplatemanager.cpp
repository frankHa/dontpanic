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

#include "libdontpanic_client/actiontemplatemanager.h"
#include <QDBusConnection>
#include <libdontpanic/actiontemplate.hpp>
#include <remote_action_template_manager.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    ActionTemplateManager::ActionTemplateManager ( QObject *parent )
        : QObject ( parent )
        ,_M_remote(0)
    {
      
    }
    // ---------------------------------------------------------------------------------
    ActionTemplateManager::~ActionTemplateManager ( ){}
    // ---------------------------------------------------------------------------------
    void ActionTemplateManager::store(ActionTemplate const& p)
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
    void ActionTemplateManager::remove(ActionTemplate const& p)
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
    ActionTemplate ActionTemplateManager::load(Uuid const& id)
    {
      return _M_cache.load(id, remote());      
    }
    // ---------------------------------------------------------------------------------
    TemplateList ActionTemplateManager::allActionTemplates()
    {
      return _M_cache.find_all(remote());
    }
    // ---------------------------------------------------------------------------------
    org::dontpanic::ActionTemplateManager* ActionTemplateManager::remote()
    {
      if(_M_remote == 0)
      {
	_M_remote = new org::dontpanic::ActionTemplateManager
	( "org.dontpanic", "/ActionTemplateManager", QDBusConnection::sessionBus(), this );
	if(!_M_remote->isValid())
	{
	  qWarning()<<_M_remote->lastError();
	}
	connect(_M_remote, SIGNAL( stored ( dp::ActionTemplate ) ), this, SLOT( on_stored ( dp::ActionTemplate ) ));
	connect(_M_remote, SIGNAL(removed(dp::ActionTemplate)), this, SLOT(on_removed(dp::ActionTemplate)));
	connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
    void ActionTemplateManager::on_stored(dp::ActionTemplate p)
    {
      _M_cache.store(p);
      emit stored(p);
    }
    // ---------------------------------------------------------------------------------
    void ActionTemplateManager::on_removed(dp::ActionTemplate p)
    {
      _M_cache.remove(p);
      emit removed(p);
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

