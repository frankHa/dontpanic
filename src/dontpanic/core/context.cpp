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

#include "context.h"
#include <persistencebackend.hpp>
#include <libdontpanic/dbus.hpp>
namespace dp
{
  // ---------------------------------------------------------------------------------
  Q_GLOBAL_STATIC(Context, _instance);
  // ---------------------------------------------------------------------------------
  Context* context()
  {
    return _instance;
  }
  // ---------------------------------------------------------------------------------
  Context::Context()
  {
    init();
  }
  // ---------------------------------------------------------------------------------
  dp::ActionTemplateManager* Context::actionTemplateManager()
  {
    return _M_action_template_manager;
  }
  // ---------------------------------------------------------------------------------
  dp::ProjectManager* Context::projectManager()
  {
    return _M_project_manager;
  }
  // ---------------------------------------------------------------------------------
  dp::ReportManager* Context::reportManager()
  {
    return _M_report_manager;
  }
  // ---------------------------------------------------------------------------------
  dp::TaskManager* Context::taskManager()
  {
    return _M_task_manager;
  }
  // ---------------------------------------------------------------------------------
  dp::TimeTracker* Context::timeTracker()
  {
    return _M_timetracker;
  }
  // ---------------------------------------------------------------------------------
  dp::PlannedWorkingTimeManager* Context::plannedWorkingtimeManager()
  {
    return _M_planned_working_time_manager;
  }
  // ---------------------------------------------------------------------------------
  // private stuff:
  // ---------------------------------------------------------------------------------
  void Context::init()
  {
    init_storage_backend();
    init_action_template_manager();
    init_projectmanager();
    init_reportmanager();
    init_taskmanager();
    init_timetracker();
    init_planned_workingtime_manager();
  }
  // ---------------------------------------------------------------------------------
  bool Context::init_storage_backend()
  {
    return dp::persistence().init("sqlite");
  }
  // ---------------------------------------------------------------------------------
  void Context::init_projectmanager()
  {
    _M_project_manager = new dp::ProjectManager ( this );
    dp::dbus().register_object ( _M_project_manager ).at_session_bus().as ( "/ProjectManager" );
  }
  // ---------------------------------------------------------------------------------
  void Context::init_taskmanager()
  {
    _M_task_manager = new dp::TaskManager ( this );
    dp::dbus().register_object ( _M_task_manager ).at_session_bus().as ( "/TaskManager" );
  }
  // ---------------------------------------------------------------------------------
  void Context::init_action_template_manager()
  {
    _M_action_template_manager = new dp::ActionTemplateManager ( this );
    dp::dbus().register_object ( _M_action_template_manager ).at_session_bus().as ( "/ActionTemplateManager" );
  }
  // ---------------------------------------------------------------------------------
  void Context::init_reportmanager()
  {
    _M_report_manager = new dp::ReportManager ( this );
    dp::dbus().register_object ( _M_report_manager ).at_session_bus().as ( "/ReportManager" );
  }
  // ---------------------------------------------------------------------------------
  void Context::init_timetracker()
  {
    _M_timetracker = new dp::TimeTracker ( this );
    dp::dbus().register_object ( _M_timetracker ).at_session_bus().as ( "/TimeTracker" );
  }
  // ---------------------------------------------------------------------------------
  void Context::init_planned_workingtime_manager()
  {
    _M_planned_working_time_manager = new dp::PlannedWorkingTimeManager ( this );
    dp::dbus().register_object ( _M_planned_working_time_manager ).at_session_bus().as ( "/PlannedWorkingTimeManager" );
  }
  // ---------------------------------------------------------------------------------
}

