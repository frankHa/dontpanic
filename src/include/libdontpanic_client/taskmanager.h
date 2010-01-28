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

#ifndef DP_CLIENT_TASKMANAGER_H
#define DP_CLIENT_TASKMANAGER_H

#include <libdontpanic/dp_export.hpp>
#include <QObject>
#include <libdontpanic/task.hpp>
#include <libdontpanic_client/detail/cache.hpp>


class OrgDontpanicTaskManagerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicTaskManagerInterface TaskManager;
  }
}


namespace dp
{

  namespace client
  {

    class DP_EXPORT TaskManager: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------	
        typedef detail::cache<Task, NullTask> cache_t;
        // ---------------------------------------------------------------------------------    
      signals:
        // ---------------------------------------------------------------------------------
        void stored(dp::Task);
        // ---------------------------------------------------------------------------------
        void removed(dp::Task);
        // ---------------------------------------------------------------------------------
        void error(QString);
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_stored(dp::Task);
        // ---------------------------------------------------------------------------------
        void on_removed(dp::Task);
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        TaskManager ( QObject *parent = 0 );
        ~TaskManager ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void store ( Task const& p );
        // ---------------------------------------------------------------------------------
        void remove(Task const& p);
        // ---------------------------------------------------------------------------------
        Task load(QUuid const& p);
        // ---------------------------------------------------------------------------------
        TaskList allTasks();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::TaskManager *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::TaskManager *_M_remote;
        // ---------------------------------------------------------------------------------
        cache_t _M_cache;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
