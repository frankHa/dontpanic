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

#ifndef DP_CLIENT_TIMETRACKER_H
#define DP_CLIENT_TIMETRACKER_H

#include <libdontpanic/dp_export.hpp>
#include <QObject>
#include <libdontpanic/action.hpp>


class OrgDontpanicTimeTrackerInterface;
namespace org
{
  namespace dontpanic
  {
    typedef OrgDontpanicTimeTrackerInterface TimeTracker;
  }
}


namespace dp
{
  class ActionTemplate;
  namespace client
  {

    class DP_EXPORT TimeTracker: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------	
      signals:
        // ---------------------------------------------------------------------------------
        void stored(dp::Action);
        // ---------------------------------------------------------------------------------
        void removed(dp::Action);
        // ---------------------------------------------------------------------------------
        void error(QString);
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        TimeTracker ( QObject *parent = 0 );
        ~TimeTracker ( );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------      
        void startNewAction();
        // ---------------------------------------------------------------------------------      
        void stopCurrentAction();
        // ---------------------------------------------------------------------------------      
        void continueLastAction();
        // ---------------------------------------------------------------------------------      
        void startActionFromTemplate(ActionTemplate const& t);
        // ---------------------------------------------------------------------------------  
        void remove(Action const& a);
        // ---------------------------------------------------------------------------------  
        void store(Action const& a);
        // ---------------------------------------------------------------------------------  
        ActionList findAll(QDate const& day);
        // ---------------------------------------------------------------------------------      
        ActionList findAll(QDate const& from, QDate const& to);
        // ---------------------------------------------------------------------------------
        ActionList findAll(QDateTime const& from, QDateTime const& to);
        // ---------------------------------------------------------------------------------      
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::TimeTracker *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        org::dontpanic::TimeTracker *_M_remote;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
