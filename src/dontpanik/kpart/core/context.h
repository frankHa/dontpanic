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

#ifndef DP_CORE_CONTEXT_H
#define DP_CORE_CONTEXT_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic_client/actiontemplatemanager.h>
#include <libdontpanic_client/projectmanager.h>
#include <libdontpanic_client/reportmanager.h>
#include <libdontpanic_client/taskmanager.h>
#include <libdontpanic_client/timetracker.h>

#include <QObject>

namespace dp
{

  namespace core
  {

    class Context: public QObject
    {
        // ---------------------------------------------------------------------------------
        Q_OBJECT
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        Context();
        ~Context();
        // ---------------------------------------------------------------------------------
      public slots:
        // ---------------------------------------------------------------------------------
        void setCurrentDate(QDate const& );
        // ---------------------------------------------------------------------------------
      public:
        // ---------------------------------------------------------------------------------
        dp::client::ActionTemplateManager* actionTemplateManager();
        // ---------------------------------------------------------------------------------
        dp::client::ProjectManager* projectManager();
        // ---------------------------------------------------------------------------------
        dp::client::ReportManager* reportManager();
        // ---------------------------------------------------------------------------------
        dp::client::TaskManager* taskManager();
        // ---------------------------------------------------------------------------------
        dp::client::TimeTracker* timeTracker();
        // ---------------------------------------------------------------------------------
        QDate currentDate() const;
        // ---------------------------------------------------------------------------------
      private:
        // ---------------------------------------------------------------------------------
        dp::client::ActionTemplateManager *_M_action_template_manager;
        // ---------------------------------------------------------------------------------
        dp::client::ProjectManager *_M_project_manager;
        // ---------------------------------------------------------------------------------
        dp::client::ReportManager *_M_report_manager;
        // ---------------------------------------------------------------------------------
        dp::client::TaskManager *_M_task_manager;
        // ---------------------------------------------------------------------------------
        dp::client::TimeTracker *_M_timetracker;
        // ---------------------------------------------------------------------------------
        QDate _M_current_date;
        // ---------------------------------------------------------------------------------
    };
    // ---------------------------------------------------------------------------------
    Context* context();
    // ---------------------------------------------------------------------------------
  }

}

#endif // DP_CORE_CONTEXT_H
