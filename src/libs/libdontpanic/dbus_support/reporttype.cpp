#include <libdontpanic/dbus_support/reporttype.h>
#include <libdontpanic/dbus_support/reportdatafilter.h>
#include <libdontpanic/dbus_support/uuid.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, ReportType & report_type )
  {
    Uuid _id;
    QString _name;
    QString _icon;
    bool _enable_alarm;
    int _ai;
    QDateTime _na;
    bool _a;
    bool _p;
    int _t;
    QString _f;
    bool _em;
    QString _dmb;
    QStringList &_er = report_type.mailRecipients();
    ReportDataFilter &_af = report_type.taskFilter();
    ReportDataFilter &_pf = report_type.projectFilter();
    QString _dsi;
    arg.beginStructure();
    arg >> _id >> _name >> _icon >> _enable_alarm >> _ai >> _na >> _a >> _p >> _t >> _af >> _pf >> _f >> _em >> _dmb >> _er >> _dsi;
    arg.endStructure();
    report_type._M_id = _id;
    report_type.setName ( _name );
    report_type.setIcon ( _icon );
    report_type.enableReportExportAlarm ( _enable_alarm );
    report_type.setReportExportAlarmInterval ( _ai );
    report_type.setNextReportExportAlarm ( _na );
    report_type.setGroupByTask ( _a );
    report_type.setGroupByProject ( _p );
    report_type.setGroupByTimeInterval ( _t );
    report_type.setExportDataFileTemplate ( _f );
    report_type.setEnableEmailExport ( _em );
    report_type.setDefaultMailBody ( _dmb );
    report_type.setDefaultMailSenderId ( _dsi );
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, ReportType const& rt )
  {
    arg.beginStructure();
    arg << rt.id() << rt.name() << rt.icon() << rt.isReportExportAlarmEnabled()
    << rt.reportExportAlarmInterval() << rt.nextReportExportAlarm()
    << rt.groupByTask() << rt.groupByProject() << rt.groupByTimeInterval() << rt.taskFilter() << rt.projectFilter() << rt.exportDataFileTemplate()
    << rt.isEmailExportEnabled() << rt.defaultMailBody() << rt.mailRecipients() << rt.defaultMailSenderId();
    arg.endStructure();
    return arg;
  }
// ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
