#include "dontpanicengine.h"

#include <QDate>
#include <QTime>

#include <libdontpanic/dbus.hpp>
#include <libdontpanic_client/actiontemplatemanager.h>
#include <libdontpanic_client/timetracker.h>
#include <libdontpanic_client/projectmanager.h>
#include <libdontpanic_client/taskmanager.h>
#include <Plasma/DataContainer>

namespace dp
{
namespace plasma
{
DontPanicEngine::DontPanicEngine(QObject* parent, const QVariantList& args)
        : Plasma::DataEngine(parent, args)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)

    // This prevents applets from setting an unnecessarily high
    // update interval and using too much CPU.
    // In the case of a clock that only has second precision,
    // a third of a second should be more than enough.
    setMinimumPollingInterval(500);
}

void DontPanicEngine::init()
{
    dbus().register_dp_custom_types();
    _M_action_template_manager = new dp::client::ActionTemplateManager();
    _M_project_manager = new dp::client::ProjectManager();
    _M_task_manager = new dp::client::TaskManager();
    _M_timetracker = new dp::client::TimeTracker();
    _M_timetracker->hasActionsFor(QDate::currentDate());
}

bool DontPanicEngine::sourceRequestEvent(const QString &name)
{
    // We do not have any special code to execute the
    // first time a source is requested, so we just call
    // updateSourceEvent().
    return updateSourceEvent(name);
}

bool DontPanicEngine::updateSourceEvent(const QString &name)
{
    if(name=="today")
    {
      setData(name, I18N_NOOP("Time"), QTime::currentTime());
      return true;
    }
    if(name=="current activity")
    {
      Action const& a = _M_timetracker->currentlyActiveAction();
      setData(name, "active", a.isActive());
      setData(name, "project", _M_project_manager->load(a.project()).name());
      setData(name, "task", _M_task_manager->load(a.task()).name());
      setData(name, "start", a.startTime());
      setData(name, "duration", a.duration());
      return true;
    }
    return true;
}

QStringList DontPanicEngine::sources() const
{
    return QStringList()<<"today"<<"current activity";
}
}
}
// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
K_EXPORT_PLASMA_DATAENGINE(dontpanic, dp::plasma::DontPanicEngine)

// this is needed since DontPanicEngine is a QObject
#include "dontpanicengine.moc"
