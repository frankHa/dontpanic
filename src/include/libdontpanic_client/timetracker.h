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
        void currentlyActiveActionChanged(dp::Action);
        // ---------------------------------------------------------------------------------        
      public:
        // ---------------------------------------------------------------------------------
        TimeTracker ( QObject *parent = 0 );
        ~TimeTracker ( );
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------      
        void startNewAction();
        // ---------------------------------------------------------------------------------      
        void stopCurrentAction();
        // ---------------------------------------------------------------------------------      
        void continueLastAction();
        // ---------------------------------------------------------------------------------
        void continueAction(Action const& a);
        // ---------------------------------------------------------------------------------      
        void startActionFromTemplate(ActionTemplate const& t);
        void startActionFromTemplate(Uuid const& t);
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
        bool hasActionsFor(QDate const& day);
        // ---------------------------------------------------------------------------------      
        Action currentlyActiveAction()const;
        // ---------------------------------------------------------------------------------      
      private slots:
        // ---------------------------------------------------------------------------------      
        void on_stored(dp::Action const&);
        // ---------------------------------------------------------------------------------      
        void on_removed(dp::Action const&);
        // ---------------------------------------------------------------------------------      
        void reset_remote_object();
        // ---------------------------------------------------------------------------------      
      private:
        // ---------------------------------------------------------------------------------
        void setCurrentlyActiveAction(dp::Action const& a);
        // ---------------------------------------------------------------------------------
        org::dontpanic::TimeTracker *remote();
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        // ---------------------------------------------------------------------------------
        org::dontpanic::TimeTracker *_M_remote;
        // ---------------------------------------------------------------------------------
        ActionList _M_latest_actions;
        // ---------------------------------------------------------------------------------
        Action _M_current_action;
        // ---------------------------------------------------------------------------------
    };

  }

}

#endif // DP_CLIENT_PROJECTMANAGER_H
