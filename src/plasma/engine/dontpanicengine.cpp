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
#include <QTimerEvent>
namespace dp
{
namespace plasma
{
  QString src_today("dp/today");
  QString src_current_activity("dp/current activity");
  QString src_favorites("dp/favorites/");
  
DontPanicEngine::DontPanicEngine(QObject* parent, const QVariantList& args)
        : Plasma::DataEngine(parent, args)
        , _M_timer_id(0)
        , _M_cached_duration(0)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)

    // This prevents applets from setting an unnecessarily high
    // update interval and using too much CPU.
    // In the case of a clock that only has second precision,
    // a third of a second should be more than enough.
    setMinimumPollingInterval(500);
    _M_sources<<src_today<<src_current_activity;
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
    init_favorites();
    
}

bool DontPanicEngine::sourceRequestEvent(const QString &name)
{
    if(name == src_current_activity)
    {
      connect(_M_timetracker, SIGNAL(currentlyActiveActionChanged(dp::Action)), this, SLOT(updateCurrentActivity()));
      return updateCurrentActivity();
    }
    if(name == src_today)
    {
      connect(_M_actions_cache, SIGNAL(timerangeChanged()), this, SLOT(updateTodaysDuration()));
      connect(_M_actions_cache, SIGNAL(stored(dp::Action)), this, SLOT(updateTodaysDuration()));
      connect(_M_actions_cache, SIGNAL(removed(dp::Action)), this, SLOT(updateTodaysDuration()));
      connect(_M_timetracker, SIGNAL(currentlyActiveActionChanged(dp::Action)), this, SLOT(updateTodaysDuration()));
      return updateTodaysDuration();
    }
    if(name.startsWith(src_favorites))
    {
      return updateFavorite(src_favorites);
    }
    return updateSourceEvent(name);
}

bool DontPanicEngine::updateSourceEvent(const QString &name)
{
    if(name==src_today)
    {
      return updateTodaysDuration();
    }
    if(name==src_current_activity)
    {
     return updateCurrentActivity();      
    }
    if(name.startsWith(src_favorites))
    {
      return updateFavorite(src_favorites);
    }
    return false;
}

QStringList DontPanicEngine::sources() const
{
    return _M_sources;
}


bool DontPanicEngine::updateTodaysDuration()
{
  _M_cached_duration = _M_actions_cache->duration();
  setData(src_today, I18N_NOOP("Time"), _M_cached_duration);
  ensure_correct_timer_state();
  return true;
}

void DontPanicEngine::init_favorites()
{
  connect(_M_action_template_manager, SIGNAL(stored(dp::ActionTemplate)), this, SLOT(updateFavorite(dp::ActionTemplate const& )));
  connect(_M_action_template_manager, SIGNAL(removed(dp::ActionTemplate)), this, SLOT(removeFavorite(dp::ActionTemplate const& )));
  TemplateList list = _M_action_template_manager->allActionTemplates();
  for(int i=0;i< list.length();++i)
  {
    updateFavorite(list.value(i));
  }
}


bool DontPanicEngine::updateCurrentActivity()
{
  Action const& a = _M_timetracker->currentlyActiveAction();
  setData(src_current_activity, "active", a.isActive());
  setData(src_current_activity, "project", _M_project_manager->load(a.project()).name());
  setData(src_current_activity, "task", _M_task_manager->load(a.task()).name());
  setData(src_current_activity, "start", a.startTime());
  setData(src_current_activity, "duration", a.duration());
  ensure_correct_timer_state();
  return true;
}

bool DontPanicEngine::updateFavorite(QString src_name)
{
  QString const& key = src_name.right(uuid().toString().length());
  ActionTemplate const& templ = _M_action_template_manager->load(Uuid(key));
  if(!templ.isValid())
  {
    return false;
  }
  return updateFavorite(templ);  
}

bool DontPanicEngine::updateFavorite(dp::ActionTemplate const& at)
{
  QString key = src_favorites + at.id().toString();
  if(!_M_sources.contains(key))
  {
    _M_sources<<key;
  }
  setData(key, "name", at.name());
  setData(key, "icon", at.icon());
  return true;
}

bool DontPanicEngine::removeFavorite(dp::ActionTemplate const& at)
{
  QString const& key = src_favorites + at.id().toString();
  _M_sources.removeAll(key);
  removeSource(key);
  return true;
}

void DontPanicEngine::timerEvent(QTimerEvent *event)
{
  if(event->timerId() == _M_timer_id)
  {
    if(_M_cached_duration == _M_actions_cache->duration())
    {
      return;
    }
    updateCurrentActivity();
    updateTodaysDuration();
  }
  Plasma::DataEngine::timerEvent(event);
}

void DontPanicEngine::ensure_correct_timer_state()
{
  if(_M_timetracker->currentlyActiveAction().isActive())
  {
    if(_M_timer_id==0)
    {
      _M_timer_id = startTimer(1000);
    }
  } else
  {
    if(_M_timer_id  != 0)
    {
      killTimer(_M_timer_id);
      _M_timer_id = 0;
    }
  }
}
}
}
// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
K_EXPORT_PLASMA_DATAENGINE(dontpanic, dp::plasma::DontPanicEngine)

// this is needed since DontPanicEngine is a QObject
#include "dontpanicengine.moc"
