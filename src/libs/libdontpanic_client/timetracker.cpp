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
	//connect(_M_remote, SIGNAL( stored ( dp::Task ) ), this, SIGNAL( stored ( dp::Task ) ));
	//connect(_M_remote, SIGNAL(removed(dp::Task)), this, SIGNAL(removed(dp::Task)));
	connect(_M_remote, SIGNAL(error(QString const&)), this, SIGNAL(error(QString)));
      }
      return _M_remote;
    }
    // ---------------------------------------------------------------------------------
  }//client
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------

