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

#ifndef DP_PERSISTENCEENGINE_H
#define DP_PERSISTENCEENGINE_H
#include <libdontpanic/defines.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  //forward decl:
  class Action;
  class ActionList;
  class Project;
  typedef QList<Project> ProjectList;
  class Task;
  typedef QList<Task> TaskList;
  class ActionTemplate;
  typedef QList<ActionTemplate> TemplateList;
  class WorktimePerDay;
  typedef QList<WorktimePerDay> WorktimePerDayList;
  class ReportType;
  typedef QList<ReportType> ReportTypeList;
  // ---------------------------------------------------------------------------------
  class PersistenceEngine
        : public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      PersistenceEngine ( QObject* parent = 0 );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      virtual ~PersistenceEngine();
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      virtual bool init() = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( WorktimePerDay const&_wt ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success load ( WorktimePerDay & _wt ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( WorktimePerDay const& _wt ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( WorktimePerDayList &_pl ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( Project const&_project ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success load ( Project & _project ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( Project const& _project ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( ProjectList &_pl ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( Task const&_t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success load ( Task & _t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( Task const& _t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( TaskList &_tl ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( ActionTemplate const&_t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success load ( ActionTemplate &_t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( ActionTemplate const& _t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( TemplateList &_tl ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( Action const&_a ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( Action const&_a ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( ActionList &_tl, QDateTime const& from,  QDateTime const& to ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual Action lastAction() const = 0;
      // ---------------------------------------------------------------------------------
      virtual bool hasActionsFor ( QDate const& date ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persistCurrentHolidayRegion ( QString const& region ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success removeCurrentHolidayRegion() const = 0;
      // ---------------------------------------------------------------------------------
      virtual success loadCurrentHolidayRegion ( QString & region ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success persist ( ReportType const&_t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success load ( ReportType & _t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success remove ( ReportType const& _t ) const = 0;
      // ---------------------------------------------------------------------------------
      virtual success findAll ( ReportTypeList &_tl ) const = 0;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_PERSTENCEENGINE_H
