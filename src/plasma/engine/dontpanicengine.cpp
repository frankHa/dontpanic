#include "dontpanicengine.h"

#include <QDate>
#include <QTime>

#include <libdontpanic/dbus.hpp>
#include <libdontpanic_client/actionscache.h>
#include <libdontpanic_client/actiontemplatemanager.h>
#include <libdontpanic_client/timetracker.h>
#include <libdontpanic_client/projectmanager.h>
#include <libdontpanic_client/taskmanager.h>

#include <Plasma/DataContainer>

namespace dp
{
namespace plasma
{
  QString src_today("dp/today");
  QString src_current_activity("dp/current activity");
  
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
    _M_action_template_manager = new dp::client::ActionTemplateManager(this);
    _M_project_manager = new dp::client::ProjectManager(this);
    _M_task_manager = new dp::client::TaskManager(this);
    _M_timetracker = new dp::client::TimeTracker(this);
    _M_actions_cache = new dp::client::ActionsCache(this);
    _M_actions_cache->setSourceTimeTracker(_M_timetracker);
    _M_actions_cache->initCache(QDate::currentDate());
    connect(_M_timetracker, SIGNAL(currentlyActiveActionChanged(dp::Action)), this, SLOT(updateCurrentActivity()));
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
    if(name==src_today)
    {
      updateTodaysDuration();
      return true;
    }
    if(name==src_current_activity)
    {
      updateCurrentActivity();      
      return true;
    }
    return true;
}

void DontPanicEngine::updateTodaysDuration()
{
  setData(src_today, I18N_NOOP("Time"), _M_actions_cache->duration());
}

void DontPanicEngine::updateCurrentActivity()
{
  Action const& a = _M_timetracker->currentlyActiveAction();
  setData(src_current_activity, "active", a.isActive());
  setData(src_current_activity, "project", _M_project_manager->load(a.project()).name());
  setData(src_current_activity, "task", _M_task_manager->load(a.task()).name());
  setData(src_current_activity, "start", a.startTime());
  setData(src_current_activity, "duration", a.duration());
}

QStringList DontPanicEngine::sources() const
{
    return QStringList()<<src_today<<src_current_activity;
}
}
}
// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
K_EXPORT_PLASMA_DATAENGINE(dontpanic, dp::plasma::DontPanicEngine)

// this is needed since DontPanicEngine is a QObject
#include "dontpanicengine.moc"
