#include "persistence/sqlite/reporttype.hpp"
#include "libdontpanic/reporttype.h"
#include "persistence/execute_query.hpp"
#include "transaction.h"
//Qt includes
#include <QVariant>
//KDE includes
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace _persistence
  {
    // ---------------------------------------------------------------------------------
    namespace _sqlite
    {
      // ---------------------------------------------------------------------------------
      const QString CREATE_TABLE_REPORT_TYPE =
        "CREATE TABLE IF NOT EXISTS r_report_type \
        (r_id TEXT PRIMARY KEY, r_name TEXT, r_icon TEXT, r_enable_export_alarm INTEGER, r_export_alarm_interval INTEGER, r_next_export_alarm TEXT, r_group_by_activity INTEGER, r_group_by_project INTEGER, r_group_by_time_interval INTEGER, r_task_filter INTEGER, r_project_filter INTEGER, r_data_export_file_template TEXT, r_enable_email_export INTEGER, r_default_mail_body TEXT, r_default_sender_id TEXT)";
      // ---------------------------------------------------------------------------------
      const QString CREATE_TABLE_REPORT_TYPE_PROJECTS =
        "CREATE TABLE IF NOT EXISTS r_report_type_projects \
      (rp_r_id TEXT, rp_p_id TEXT)";
      // ---------------------------------------------------------------------------------
      const QString CREATE_TABLE_REPORT_TYPE_TASKS =
        "CREATE TABLE IF NOT EXISTS r_report_type_tasks \
      (rp_r_id TEXT, rp_t_id TEXT)";
      // ---------------------------------------------------------------------------------
      const QString CREATE_TABLE_REPORT_TYPE_EMAIL_RECIPIENTS =
        "CREATE TABLE IF NOT EXISTS r_report_type_email_recipients \
      (rr_r_id TEXT, rr_email TEXT)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_REPORT_TYPE =
        "INSERT INTO r_report_type(r_id, r_name, r_icon, r_enable_export_alarm , r_export_alarm_interval , r_next_export_alarm, r_group_by_activity, r_group_by_project, r_group_by_time_interval, r_task_filter, r_project_filter, r_data_export_file_template, r_enable_email_export, r_default_mail_body, r_default_sender_id)VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_ALL_REPORT_TYPES =
        "SELECT r_id, r_name, r_icon, r_enable_export_alarm , r_export_alarm_interval , r_next_export_alarm, r_group_by_activity, r_group_by_project, r_group_by_time_interval, r_task_filter, r_project_filter, r_data_export_file_template, r_enable_email_export, r_default_mail_body, r_default_sender_id FROM r_report_type order by r_name";
      // ---------------------------------------------------------------------------------
      const QString SELECT_DISTINCT_REPORT_TYPE =
        "SELECT DISTINCT r_id, r_name, r_icon, r_enable_export_alarm , r_export_alarm_interval , r_next_export_alarm, r_group_by_activity, r_group_by_project, r_group_by_time_interval, r_task_filter, r_project_filter, r_data_export_file_template, r_enable_email_export, r_default_mail_body, r_default_sender_id FROM r_report_type WHERE (r_id=?)";
      // ---------------------------------------------------------------------------------
      const QString UPDATE_REPORT_TYPE =
        "UPDATE r_report_type set r_name=?, r_icon=?, r_enable_export_alarm=? , r_export_alarm_interval=? , r_next_export_alarm=?, r_group_by_activity=?, r_group_by_project=?, r_group_by_time_interval=?, r_task_filter=?, r_project_filter=?, r_data_export_file_template=?, r_enable_email_export=?, r_default_mail_body=?, r_default_sender_id=? WHERE (r_id=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_REPORT_TYPE =
        "DELETE FROM r_report_type WHERE (r_id=?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_PROJECTS =
        "SELECT rp_p_id from r_report_type_projects WHERE (rp_r_id = ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_TASKS =
        "SELECT rp_t_id from r_report_type_tasks WHERE (rp_r_id = ?)";
      // ---------------------------------------------------------------------------------
      const QString SELECT_EMAIL_RECIPIENTS =
        "SELECT rr_email from r_report_type_email_recipients WHERE (rr_r_id = ?)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_PROJECT =
        "INSERT INTO r_report_type_projects (rp_r_id, rp_p_id)VALUES(?,?)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_TASK =
        "INSERT INTO r_report_type_tasks (rp_r_id, rp_t_id)VALUES(?,?)";
      // ---------------------------------------------------------------------------------
      const QString INSERT_EMAIL_RECIPIENT =
        "INSERT INTO r_report_type_email_recipients (rr_r_id, rr_email)VALUES(?,?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_PROJECTS =
        "DELETE FROM r_report_type_projects WHERE (rp_r_id=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_TASKS =
        "DELETE FROM r_report_type_tasks WHERE (rp_r_id=?)";
      // ---------------------------------------------------------------------------------
      const QString REMOVE_EMAIL_RECIPIENTS =
        "DELETE FROM r_report_type_email_recipients WHERE (rr_r_id=?)";
      // ---------------------------------------------------------------------------------
      // public stuff:
      // ---------------------------------------------------------------------------------
      success _sqlite::ReportType::create_table()
      {
        QSqlQuery query;
        query.prepare ( CREATE_TABLE_REPORT_TYPE );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          result = create_project_filter_table();
        }
        if ( result.was_successful() )
        {
          result = create_task_filter_table();
        }
        if ( result.was_successful() )
        {
          result = create_email_recipients_table();
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::persist ( dp::ReportType const&_project ) const
      {
        if ( exists ( _project ) )
        {
          return update ( _project );
        }
        return insert ( _project );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::remove ( dp::ReportType const& _rt ) const
      {
        Transaction transaction;
        if ( _rt.id().isNull() )
        {
          return error();
        }
        if ( !exists ( _rt ) )
        {
          return successful();
        }
        QSqlQuery query;
        query.prepare ( REMOVE_REPORT_TYPE );
        query.addBindValue ( _rt.id().toString() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          result = remove_selected_projects ( _rt );
        }
        if ( result.was_successful() )
        {
          result = remove_selected_tasks ( _rt );
        }
        if ( result.was_successful() )
        {
          result = remove_selected_email_recipients ( _rt );
        }
        if ( result.was_successful() )
        {
          transaction.commit();
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::load ( dp::ReportType &_rt ) const
      {
        if ( _rt.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_REPORT_TYPE );
        query.addBindValue ( _rt.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          qWarning() << "last error: " << query.lastError();
          return error();
        }
        if ( !query.first() )
        {
          qWarning() << "last error: " << query.lastError();
          return error();
        }
        success result = assign_query_values_to_entity ( query, _rt );
        if ( result.was_successful() )
        {
          result = load_selected_projects ( _rt );
        }
        if ( result.was_successful() )
        {
          result = load_selected_tasks ( _rt );
        }
        if ( result.was_successful() )
        {
          result = load_selected_email_recipients ( _rt );
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::findAll ( dp::ReportTypeList &l ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_ALL_REPORT_TYPES );
        if ( execute ( query ).has_failed() )
        {
          return error();
        }
        while ( query.next() )
        {
          dp::ReportType _p ( Uuid ( query.value ( 0 ).toString() ) );
          assign_query_values_to_entity ( query, _p );
          load_selected_projects ( _p );
          load_selected_tasks ( _p );
          load_selected_email_recipients ( _p );
          l.append ( _p );
        }
        return successful();
      }
      // ---------------------------------------------------------------------------------
      // private stuff:
      // ---------------------------------------------------------------------------------
      success ReportType::create_project_filter_table() const
      {
        QSqlQuery query;
        query.prepare ( CREATE_TABLE_REPORT_TYPE_PROJECTS );
        success result = execute ( query );
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::create_task_filter_table() const
      {
        QSqlQuery query;
        query.prepare ( CREATE_TABLE_REPORT_TYPE_TASKS );
        success result = execute ( query );
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::create_email_recipients_table() const
      {
        QSqlQuery query;
        query.prepare ( CREATE_TABLE_REPORT_TYPE_EMAIL_RECIPIENTS );
        success result = execute ( query );
        return result;
      }
      // ---------------------------------------------------------------------------------
      bool ReportType::exists ( const dp::ReportType& _project ) const
      {
        if ( _project.id().isNull() )
        {
          return false;
        }
        QSqlQuery query;
        query.prepare ( SELECT_DISTINCT_REPORT_TYPE );
        query.addBindValue ( _project.id().toString() );
        if ( execute ( query ).has_failed() )
        {
          return false;
        }
        return query.first();
      }
      // ---------------------------------------------------------------------------------
      success ReportType::insert ( dp::ReportType const& _p ) const
      {
        Transaction transaction;
        if ( _p.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( INSERT_REPORT_TYPE );
        query.addBindValue ( _p.id().toString() );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.icon() );
        query.addBindValue ( _p.isReportExportAlarmEnabled() );
        query.addBindValue ( _p.reportExportAlarmInterval() );
        bindTimeValue ( query, _p.nextReportExportAlarm() );
        query.addBindValue ( _p.groupByTask() );
        query.addBindValue ( _p.groupByProject() );
        query.addBindValue ( _p.groupByTimeInterval() );
        query.addBindValue ( _p.taskFilter().filterType() );
        query.addBindValue ( _p.projectFilter().filterType() );
        query.addBindValue ( _p.exportDataFileTemplate() );
        query.addBindValue ( _p.isEmailExportEnabled() );
        query.addBindValue ( _p.defaultMailBody() );
        query.addBindValue ( _p.defaultMailSenderId() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          result = update_selected_projects ( _p );
        }
        if ( result.was_successful() )
        {
          result = update_selected_tasks ( _p );
        }
        if ( result.was_successful() )
        {
          result = update_selected_email_recipients ( _p );
        }
        if ( result.was_successful() )
        {
          transaction.commit();
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::update ( const dp::ReportType& _p ) const
      {
        Transaction transaction;
        if ( _p.id().isNull() )
        {
          return error();
        }
        QSqlQuery query;
        query.prepare ( UPDATE_REPORT_TYPE );
        query.addBindValue ( _p.name() );
        query.addBindValue ( _p.icon() );
        query.addBindValue ( _p.isReportExportAlarmEnabled() );
        query.addBindValue ( _p.reportExportAlarmInterval() );
        bindTimeValue ( query, _p.nextReportExportAlarm() );
        query.addBindValue ( _p.groupByTask() );
        query.addBindValue ( _p.groupByProject() );
        query.addBindValue ( _p.groupByTimeInterval() );
        query.addBindValue ( _p.taskFilter().filterType() );
        query.addBindValue ( _p.projectFilter().filterType() );
        query.addBindValue ( _p.exportDataFileTemplate() );
        query.addBindValue ( _p.isEmailExportEnabled() );
        query.addBindValue ( _p.defaultMailBody() );
        query.addBindValue ( _p.defaultMailSenderId() );
        query.addBindValue ( _p.id().toString() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          result = update_selected_projects ( _p );
        }
        if ( result.was_successful() )
        {
          result = update_selected_tasks ( _p );
        }
        if ( result.was_successful() )
        {
          result = update_selected_email_recipients ( _p );
        }
        if ( result.was_successful() )
        {
          transaction.commit();
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::load_selected_projects ( dp::ReportType & _p ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_PROJECTS );
        query.addBindValue ( _p.id().toString() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          while ( query.next() )
          {
            Uuid id ( query.value ( 0 ).toString() );
            _p.projectFilter().selection().append ( id );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::load_selected_tasks ( dp::ReportType & _p ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_TASKS );
        query.addBindValue ( _p.id().toString() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          while ( query.next() )
          {
            Uuid id ( query.value ( 0 ).toString() );
            _p.taskFilter().selection().append ( id );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::load_selected_email_recipients ( dp::ReportType & _p ) const
      {
        QSqlQuery query;
        query.prepare ( SELECT_EMAIL_RECIPIENTS );
        query.addBindValue ( _p.id().toString() );
        success result = execute ( query );
        if ( result.was_successful() )
        {
          while ( query.next() )
          {
            QString const& id ( query.value ( 0 ).toString() );
            _p.mailRecipients().append ( id );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::update_selected_projects ( dp::ReportType const& _p ) const
      {
        success result = remove_selected_projects ( _p );
        if ( result.was_successful() )
        {
          UuidList const& entries = _p.projectFilter().selection();
          foreach ( Uuid const& id, entries )
          {
            QSqlQuery query;
            query.prepare ( INSERT_PROJECT );
            query.addBindValue ( _p.id().toString() );
            query.addBindValue ( id.toString() );
            execute ( query );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::update_selected_tasks ( dp::ReportType const& _p ) const
      {
        success result = remove_selected_tasks ( _p );
        if ( result.was_successful() )
        {
          UuidList const& entries = _p.taskFilter().selection();
          foreach ( Uuid const& id, entries )
          {
            QSqlQuery query;
            query.prepare ( INSERT_TASK );
            query.addBindValue ( _p.id().toString() );
            query.addBindValue ( id.toString() );
            execute ( query );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::update_selected_email_recipients ( dp::ReportType const& _p ) const
      {
        success result = remove_selected_email_recipients ( _p );
        if ( result.was_successful() )
        {
          QStringList const& entries = _p.mailRecipients();
          foreach ( QString const& rec, entries )
          {
            QSqlQuery query;
            query.prepare ( INSERT_EMAIL_RECIPIENT );
            query.addBindValue ( _p.id().toString() );
            query.addBindValue ( rec );
            execute ( query );
          }
        }
        return result;
      }
      // ---------------------------------------------------------------------------------
      success ReportType::remove_selected_projects ( dp::ReportType const& _p ) const
      {
        QSqlQuery query;
        query.prepare ( REMOVE_PROJECTS );
        query.addBindValue ( _p.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::remove_selected_tasks ( dp::ReportType const& _p ) const
      {
        QSqlQuery query;
        query.prepare ( REMOVE_TASKS );
        query.addBindValue ( _p.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::remove_selected_email_recipients ( dp::ReportType const& _p ) const
      {
        QSqlQuery query;
        query.prepare ( REMOVE_EMAIL_RECIPIENTS );
        query.addBindValue ( _p.id().toString() );
        return execute ( query );
      }
      // ---------------------------------------------------------------------------------
      success ReportType::assign_query_values_to_entity ( QSqlQuery& query, dp::ReportType& p ) const
      {
        p.setName ( query.value ( 1 ).toString() );
        p.setIcon ( query.value ( 2 ).toString() ) ;
        p.enableReportExportAlarm(query.value(3).toBool());
        p.setReportExportAlarmInterval(query.value(4).toInt());
        p.setNextReportExportAlarm(query.value(5).toDateTime());
        p.setGroupByTask ( query.value ( 6 ).toBool() ) ;
        p.setGroupByProject ( query.value ( 7 ).toBool() ) ;
        p.setGroupByTimeInterval ( query.value ( 8 ).toInt() ) ;
        p.taskFilter().setFilterType ( query.value ( 9 ).toInt() ) ;
        p.projectFilter().setFilterType ( query.value ( 10 ).toInt() ) ;
        p.setExportDataFileTemplate ( query.value (11 ).toString() );
        p.setEnableEmailExport ( query.value ( 12 ).toBool() );
        p.setDefaultMailBody ( query.value ( 13 ).toString() );
        p.setDefaultMailSenderId ( query.value ( 14 ).toString() );
        return successful();
      }

      // ---------------------------------------------------------------------------------
    }//sqlite
    // ---------------------------------------------------------------------------------
  }//_persistance
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
