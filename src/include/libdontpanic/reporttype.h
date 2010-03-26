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
class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
  class ReportTypePrivate;
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
      QString title() const;
      // ---------------------------------------------------------------------------------
      ReportType& setTitle ( QString title );
      // ---------------------------------------------------------------------------------
      ReportType& setGroupByActivity(bool b);
      // ---------------------------------------------------------------------------------
      bool groupByActivity() const;
      // ---------------------------------------------------------------------------------
      ReportType& setGroupByProject(bool b);
      // ---------------------------------------------------------------------------------
      bool groupByProject() const;
      // ---------------------------------------------------------------------------------
      ReportDataFilter & activityFilter();
      ReportDataFilter const& activityFilter()const;
      // ---------------------------------------------------------------------------------
      ReportDataFilter & projectFilter();
      ReportDataFilter const& projectFilter() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Uuid _M_id;
      // ---------------------------------------------------------------------------------
      QString _M_title;
      // ---------------------------------------------------------------------------------
      bool _M_group_by_activity;
      // ---------------------------------------------------------------------------------
      bool _M_group_by_project;
      // ---------------------------------------------------------------------------------
      ReportDataFilter _M_activity_filter;
      // ---------------------------------------------------------------------------------
      ReportDataFilter _M_project_filter;
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
    out<<"ReportType: "<<p.id().toString()<<", title: "<<p.title();
    return out;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // LIBDONTPANIC_REPORTTYPE_H
