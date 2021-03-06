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

#ifndef DP_CLIENT_PROJECTMANAGER_H
#define DP_CLIENT_PROJECTMANAGER_H

#include <libdontpanic/dp_export.hpp>
#include <QObject>
#include <libdontpanic/project.hpp>
#include <libdontpanic_client/detail/cache.hpp>


class OrgDontpanicProjectManagerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicProjectManagerInterface ProjectManager;
  }
}


namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace client
  {
    // ---------------------------------------------------------------------------------
    class DP_EXPORT ProjectManager: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
        typedef detail::cache<Project, NullProject> cache_t;
        // ---------------------------------------------------------------------------------
      signals:
        // ---------------------------------------------------------------------------------
        void stored ( dp::Project );
        // ---------------------------------------------------------------------------------
        void removed ( dp::Project );
        // ---------------------------------------------------------------------------------
        void error ( QString );
        // ---------------------------------------------------------------------------------
      private slots:
        // ---------------------------------------------------------------------------------
        void on_stored ( dp::Project );
        // ---------------------------------------------------------------------------------
        void on_removed ( dp::Project );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        ProjectManager ( QObject *parent = 0 );
        ~ProjectManager ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        void store ( Project const& p );
        // ---------------------------------------------------------------------------------
        void remove ( Project const& p );
        // ---------------------------------------------------------------------------------
        Project load ( Uuid const& id );
        // ---------------------------------------------------------------------------------
        ProjectList allProjects();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ProjectManager *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::ProjectManager *_M_remote;
        // ---------------------------------------------------------------------------------
        cache_t _M_cache;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_CLIENT_PROJECTMANAGER_H
