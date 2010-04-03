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

#ifndef DP_CONTEXT_H
#define DP_CONTEXT_H
#include <libdontpanic/defines.hpp>
#include <QObject>
#include <actiontemplatemanager.h>
#include <projectmanager.h>
#include <reportmanager.h>
#include <taskmanager.h>
#include <timetracker.h>
#include <plannedworkingtimemanager.h>


namespace dp
{

  class Context
        : public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Context();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      dp::ActionTemplateManager* actionTemplateManager();
      // ---------------------------------------------------------------------------------
      dp::ProjectManager* projectManager();
      // ---------------------------------------------------------------------------------
      dp::ReportManager* reportManager();
      // ---------------------------------------------------------------------------------
      dp::TaskManager* taskManager();
      // ---------------------------------------------------------------------------------
      dp::TimeTracker* timeTracker();
      // ---------------------------------------------------------------------------------
      dp::PlannedWorkingTimeManager* plannedWorkingtimeManager();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      void init();
      // ---------------------------------------------------------------------------------
      bool init_storage_backend();
      // ---------------------------------------------------------------------------------
      void init_action_template_manager();
      // ---------------------------------------------------------------------------------
      void init_projectmanager();
      // ---------------------------------------------------------------------------------
      void init_reportmanager();
      // ---------------------------------------------------------------------------------
      void init_taskmanager();
      // ---------------------------------------------------------------------------------
      void init_timetracker();
      // ---------------------------------------------------------------------------------
      void init_planned_workingtime_manager();
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      dp::ActionTemplateManager *_M_action_template_manager;
      // ---------------------------------------------------------------------------------
      dp::ProjectManager *_M_project_manager;
      // ---------------------------------------------------------------------------------
      dp::ReportManager *_M_report_manager;
      // ---------------------------------------------------------------------------------
      dp::TaskManager *_M_task_manager;
      // ---------------------------------------------------------------------------------
      dp::TimeTracker *_M_timetracker;
      // ---------------------------------------------------------------------------------
      dp::PlannedWorkingTimeManager *_M_planned_working_time_manager;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  Context* context();
  // ---------------------------------------------------------------------------------
}

#endif // DP_CONTEXT_H
