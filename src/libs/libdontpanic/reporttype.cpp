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

#include <libdontpanic/reporttype.h>
#include <libdontpanic/report.h>
#include <libdontpanic/timerangeformatter.h>
#include <libdontpanic/reportgroupingtimeinterval.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  ///ctor
  ReportType::ReportType()
      : _M_id ( Uuid::generate() )
      , _M_name ( "" )
      , _M_icon ( "" )
      , _M_enable_report_export_alarm ( false )
      , _M_report_export_alarm_interval ( 0 )
      , _M_next_report_export_alarm ( QDateTime() )
      , _M_group_by_task ( false )
      , _M_group_by_project ( false )
      , _M_group_by_time_interval ( ReportGroupingTimeInterval::NONE )
      , _M_enable_email_export ( false )
      , _M_default_mail_body ( "" )
      , _M_default_mail_sender_id ( "" ) {}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( QString const& title )
      : _M_id ( Uuid::generate() )
      , _M_name ( title )
      , _M_icon ( "" )
      , _M_enable_report_export_alarm ( false )
      , _M_report_export_alarm_interval ( 0 )
      , _M_next_report_export_alarm ( QDateTime() )
      , _M_group_by_task ( false )
      , _M_group_by_project ( false )
      , _M_group_by_time_interval ( ReportGroupingTimeInterval::NONE )
      , _M_enable_email_export ( false )
      , _M_default_mail_body ( "" )
      , _M_default_mail_sender_id ( "" ) {}
  // ---------------------------------------------------------------------------------
  ReportType::ReportType ( Uuid const& id )
      : _M_id ( id )
      , _M_name ( "" )
      , _M_icon ( "" )
      , _M_enable_report_export_alarm ( false )
      , _M_report_export_alarm_interval ( 0 )
      , _M_next_report_export_alarm ( QDateTime() )
      , _M_group_by_task ( false )
      , _M_group_by_project ( false )
      , _M_group_by_time_interval ( ReportGroupingTimeInterval::NONE )
      , _M_enable_email_export ( false )
      , _M_default_mail_body ( "" )
      , _M_default_mail_sender_id ( "" ) {}
  // ---------------------------------------------------------------------------------
  Uuid const& ReportType::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::isValid() const
  {
    return !_M_id.isNull();
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setName ( QString title )
  {
    _M_name = title;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::icon() const
  {
    return _M_icon;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setIcon ( QString icon )
  {
    _M_icon = icon;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::enableReportExportAlarm(bool b)
  {
    _M_enable_report_export_alarm = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::isReportExportAlarmEnabled() const
  {
    return _M_enable_report_export_alarm;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setReportExportAlarmInterval(int interval)
  {
    _M_report_export_alarm_interval = interval;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  int ReportType::reportExportAlarmInterval() const
  {
    return _M_report_export_alarm_interval;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setNextReportExportAlarm(QDateTime const& dt)
  {
    _M_next_report_export_alarm = dt;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime ReportType::nextReportExportAlarm()const
  {
    return _M_next_report_export_alarm;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::noGrouping() const
  {
    if ( groupByProject() ) return false;
    if ( groupByTask() ) return false;
    if ( groupByTimeInterval() != ReportGroupingTimeInterval::NONE ) return false;
    return true;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setGroupByTask ( bool b )
  {
    _M_group_by_task = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::groupByTask() const
  {
    return _M_group_by_task;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setGroupByProject ( bool b )
  {
    _M_group_by_project = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::groupByProject() const
  {
    return _M_group_by_project;
  }
  // ---------------------------------------------------------------------------------
  int ReportType::groupByTimeInterval() const
  {
    return _M_group_by_time_interval;
  }
  // ---------------------------------------------------------------------------------
  ReportType & ReportType::setGroupByTimeInterval ( int interval_type )
  {
    _M_group_by_time_interval = interval_type;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter & ReportType::taskFilter()
  {
    return _M_task_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter const& ReportType::taskFilter() const
  {
    return _M_task_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter & ReportType::projectFilter()
  {
    return _M_project_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportDataFilter const& ReportType::projectFilter() const
  {
    return _M_project_filter;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setEnableEmailExport ( bool b )
  {
    _M_enable_email_export = b;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool ReportType::enableEmailExport() const
  {
    return _M_enable_email_export;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setDefaultMailBody ( QString const& mb )
  {
    _M_default_mail_body = mb;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::defaultMailBody() const
  {
    return _M_default_mail_body;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setDefaultMailSenderId ( QString const& id )
  {
    _M_default_mail_sender_id = id;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QStringList & ReportType::mailRecipients()
  {
    return _M_email_recipients;
  }
  // ---------------------------------------------------------------------------------
  QStringList const& ReportType::mailRecipients() const
  {
    return _M_email_recipients;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::defaultMailSenderId() const
  {
    return _M_default_mail_sender_id;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::exportDataFileTemplate() const
  {
    return _M_data_export_file_template;
  }
  // ---------------------------------------------------------------------------------
  ReportType& ReportType::setExportDataFileTemplate ( QString const& file )
  {
    _M_data_export_file_template = file;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QString ReportType::exportDataFileName ( Report const& rep ) const
  {
    QString absFilePath = _M_data_export_file_template;
    TimeRange const& range = rep.range();
    absFilePath.replace ( "<smart_timerange>", time_range_formatter().pretty_format ( range ), Qt::CaseInsensitive );
    return absFilePath;
  }
  // ---------------------------------------------------------------------------------
  bool DP_EXPORT operator == ( dp::ReportType const& lhs, dp::ReportType const& rhs )
  {
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
