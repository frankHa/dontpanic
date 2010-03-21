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

#include "libdontpanic_client/reportmanager.h"
#include <QDBusConnection>
#include <remote_reportmanager.h>
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    ReportManager::ReportManager ( QObject *parent )
        : QObject ( parent )
        ,_M_remote(0)
    {}
    // ---------------------------------------------------------------------------------
    void ReportManager::store(ReportType const& p)
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
    ReportType ReportManager::load(Uuid const& id)
    {
      return _M_cache.load(id, remote());      
    }
    // ---------------------------------------------------------------------------------
    void ReportManager::remove(ReportType const& p)
    {
      QDBusPendingReply<> reply =remote()->remove(p);
      reply.waitForFinished();
      if(reply.isError())
      {
        kWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
    }
    // ---------------------------------------------------------------------------------
    ReportTypeList ReportManager::allReportTypes()
    {
      return _M_cache.find_all(remote());
    }
    // ---------------------------------------------------------------------------------
    Report ReportManager::generateReport(ReportType const& _type, TimeRange const& range)
    {
      QDBusPendingReply<Report> reply =remote()->generateReport(_type, range);
      reply.waitForFinished();
      if(reply.isError())
      {
        kWarning()<<reply.error();
        emit error(QDBusError::errorString(reply.error().type()));
      }
      Report const& rep = reply.value();
      emit generated(rep);
      return rep;
    }
    // ---------------------------------------------------------------------------------
    ReportManager::~ReportManager ( ){}
    // ---------------------------------------------------------------------------------
    org::dontpanic::ReportManager* ReportManager::remote()
    {
      if(_M_remote == 0)
      {
        _M_remote = new org::dontpanic::ReportManager
        ( "org.dontpanic", "/ReportManager", QDBusConnection::sessionBus(), this );
        if(!_M_remote->isValid())
        {
          kWarning()<<_M_remote->lastError();
        }
         connect(_M_remote, SIGNAL( stored ( dp::ReportType ) ), this, SLOT( on_stored ( dp::ReportType ) ));
         connect(_M_remote, SIGNAL(removed(dp::ReportType)), this, SLOT(on_removed(dp::ReportType)));
         connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------    
    void ReportManager::on_stored(dp::ReportType p)
    {
      _M_cache.store(p);
      emit stored(p);
    }
    // ---------------------------------------------------------------------------------
    void ReportManager::on_removed(dp::ReportType p)
    {
      _M_cache.remove(p);
      emit removed(p);
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

