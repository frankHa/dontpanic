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
#include <QDateTime>
class QDBusArgument;
// ---------------------------------------------------------------------------------
namespace dp
{
  class ReportType;
  typedef QList<ReportType> ReportTypeList;
}
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::ReportType )
Q_DECLARE_METATYPE ( dp::ReportTypeList )
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
      ReportType& enableReportExportAlarm(bool);
      // ---------------------------------------------------------------------------------
      bool isReportExportAlarmEnabled() const;
      // ---------------------------------------------------------------------------------
      ReportType& setReportExportAlarmInterval(int);
      // ---------------------------------------------------------------------------------
      int reportExportAlarmInterval() const;
      // ---------------------------------------------------------------------------------
      ReportType& setNextReportExportAlarm(QDateTime const& dt);
      // ---------------------------------------------------------------------------------
      QDateTime nextReportExportAlarm()const;
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
      ReportType& setEnableEmailExport(bool b);
      // ---------------------------------------------------------------------------------
      bool isEmailExportEnabled() const;
      // ---------------------------------------------------------------------------------
      ReportType& setDefaultMailBody(QString const& mb);
      // ---------------------------------------------------------------------------------
      QString defaultMailBody() const;
      // ---------------------------------------------------------------------------------
      ReportType& setDefaultMailSenderId(QString const& id);
      // ---------------------------------------------------------------------------------
      QString defaultMailSenderId()const;
      // ---------------------------------------------------------------------------------
      QStringList & mailRecipients();
      QStringList const& mailRecipients() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Uuid _M_id;
      // ---------------------------------------------------------------------------------
      QString _M_name;
      // ---------------------------------------------------------------------------------
      QString _M_icon;
      // ---------------------------------------------------------------------------------
      bool _M_enable_report_export_alarm;
      // ---------------------------------------------------------------------------------
      int _M_report_export_alarm_interval;
      // ---------------------------------------------------------------------------------
      QDateTime _M_next_report_export_alarm;
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
      bool _M_enable_email_export;
      // ---------------------------------------------------------------------------------
      QString _M_default_mail_body;
      // ---------------------------------------------------------------------------------
      QString _M_default_mail_sender_id;
      // ---------------------------------------------------------------------------------
      QStringList _M_email_recipients;
      // ---------------------------------------------------------------------------------      
  };
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
