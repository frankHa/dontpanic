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

#ifndef LIBDONTPANIC_REPORTTYPE_H
#define LIBDONTPANIC_REPORTTYPE_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <libdontpanic/reportdatafilter.h>
#include <QFileInfo>
class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class Report;
  // ---------------------------------------------------------------------------------
  class DP_EXPORT ReportType
  {
    // ---------------------------------------------------------------------------------
    friend QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportType & report_type );
    // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      enum FilterType{NO_FILTER, SELECTED_ONLY, UNSELECTED_ONLY};
      // ---------------------------------------------------------------------------------
      enum TimeIntervalType{NONE, DAILY, WEEKLY, MONTHLY, QUARTERLY, YEARLY};
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TYPE ( ReportType );
      // ---------------------------------------------------------------------------------
      ///ctor
      ReportType();
      // ---------------------------------------------------------------------------------
      ReportType(QString const& title);
      // ---------------------------------------------------------------------------------
      ReportType ( Uuid const& id );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Uuid const& id() const;
      // ---------------------------------------------------------------------------------
      bool isValid() const;
      // ---------------------------------------------------------------------------------
      QString name() const;
      // ---------------------------------------------------------------------------------
      ReportType& setName ( QString name );
      // ---------------------------------------------------------------------------------
      QString icon() const;
      // ---------------------------------------------------------------------------------
      ReportType& setIcon(QString icon);
      // ---------------------------------------------------------------------------------
      ReportType& setGroupByTask(bool b);
      // ---------------------------------------------------------------------------------
      bool groupByTask() const;
      // ---------------------------------------------------------------------------------
      ReportType& setGroupByProject(bool b);
      // ---------------------------------------------------------------------------------      
      int groupByTimeInterval() const;
      // ---------------------------------------------------------------------------------
      ReportType & setGroupByTimeInterval(int interval_type);
      // ---------------------------------------------------------------------------------
      bool noGrouping() const;
      // ---------------------------------------------------------------------------------
      bool groupByProject() const;
      // ---------------------------------------------------------------------------------
      ReportDataFilter & taskFilter();
      ReportDataFilter const& taskFilter()const;
      // ---------------------------------------------------------------------------------
      ReportDataFilter & projectFilter();
      ReportDataFilter const& projectFilter() const;
      // ---------------------------------------------------------------------------------
      QString exportDataFileTemplate() const;
      // ---------------------------------------------------------------------------------
      ReportType& setExportDataFileTemplate(QString const& file);
      // ---------------------------------------------------------------------------------
      QString exportDataFileName(Report const& rep) const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Uuid _M_id;
      // ---------------------------------------------------------------------------------
      QString _M_name;
      // ---------------------------------------------------------------------------------
      QString _M_icon;
      // ---------------------------------------------------------------------------------
      bool _M_group_by_task;
      // ---------------------------------------------------------------------------------
      bool _M_group_by_project;
      // ---------------------------------------------------------------------------------
      int _M_group_by_time_interval;
      // ---------------------------------------------------------------------------------
      ReportDataFilter _M_task_filter;
      // ---------------------------------------------------------------------------------
      ReportDataFilter _M_project_filter;
      // ---------------------------------------------------------------------------------
      QString _M_data_export_file_template;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  typedef QList<ReportType> ReportTypeList;
  // ---------------------------------------------------------------------------------
  DECLARE_SMARTPOINTERS ( ReportType );
  // ---------------------------------------------------------------------------------
  class DP_EXPORT NullReportType: public ReportType
  {
    public:
      // ---------------------------------------------------------------------------------
      NullReportType() : ReportType ( Uuid() ) {}
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == (dp::ReportType const& lhs, dp::ReportType const& rhs);
  // ---------------------------------------------------------------------------------
  template<typename ostream>
  ostream & operator<<(ostream &out, dp::ReportType const& p)
  {
    out<<"ReportType: "<<p.id().toString()<<", title: "<<p.name();
    return out;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // LIBDONTPANIC_REPORTTYPE_H
