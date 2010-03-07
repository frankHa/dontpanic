#include <libdontpanic/dbus_support/worktimeperday.h>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::WorktimePerDay & wtpd )
  {
    int _d;
    QString _t;
    arg.beginStructure();
    arg >> _d >> _t;
    arg.endStructure();
    wtpd.setDay((Qt::DayOfWeek)_d);
    wtpd.setPlannedWorkingHours(QTime::fromString(_t));
    return arg;
  }
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::WorktimePerDay const& wtpd )
  {
    arg.beginStructure();
    arg << wtpd.day()<<wtpd.plannedWorkingHours().toString();
    arg.endStructure();
    return arg;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
