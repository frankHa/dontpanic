// a standard include guard to prevent problems if the
// header is included multiple times
#ifndef DONTPANICENGINE_H
#define DONTPANICENGINE_H
#include <libdontpanic/defines.hpp>
// We need the DataEngine header, since we are inheriting it
#include <Plasma/DataEngine>

namespace dp
{
  class ActionTemplate;
namespace client
{
class ActionTemplateManager;
class ProjectManager;
class TaskManager;
class TimeTracker;
class ActionsCache;
}
namespace plasma
{
class DontPanicEngine : public Plasma::DataEngine
{
    // required since Plasma::DataEngine inherits QObject
    Q_OBJECT

public:
    // every engine needs a constructor with these arguments
    DontPanicEngine(QObject* parent, const QVariantList& args);

protected:
    void init();
    // this virtual function is called when a new source is requested
    bool sourceRequestEvent(const QString& name);

    // this virtual function is called when an automatic update
    // is triggered for an existing source (ie: when a valid update
    // interval is set when requesting a source)
    bool updateSourceEvent(const QString& source);
    // ---------------------------------------------------------------------------------
    QStringList sources() const;
    // ---------------------------------------------------------------------------------
  private slots:
    // ---------------------------------------------------------------------------------
    void init_favorites();
    // ---------------------------------------------------------------------------------
    bool updateFavorite(dp::ActionTemplate const& );
    // ---------------------------------------------------------------------------------
    bool removeFavorite(dp::ActionTemplate const& t);
    // ---------------------------------------------------------------------------------
    bool updateFavorite(QString src_name);
    // ---------------------------------------------------------------------------------
    bool updateTodaysDuration();
    // ---------------------------------------------------------------------------------
    bool updateCurrentActivity();
    // ---------------------------------------------------------------------------------
    void ensure_correct_timer_state();
    // ---------------------------------------------------------------------------------
  protected:
    // ---------------------------------------------------------------------------------
    /**
    * Reimplemented from QObject
    **/
    void timerEvent(QTimerEvent *event);
    // ---------------------------------------------------------------------------------
private:
    // ---------------------------------------------------------------------------------
    dp::client::ActionTemplateManager *_M_action_template_manager;
    // ---------------------------------------------------------------------------------
    dp::client::ProjectManager *_M_project_manager;
    // ---------------------------------------------------------------------------------
    dp::client::TaskManager *_M_task_manager;
    // ---------------------------------------------------------------------------------
    dp::client::TimeTracker *_M_timetracker;
    // ---------------------------------------------------------------------------------
    dp::client::ActionsCache *_M_actions_cache;
    // ---------------------------------------------------------------------------------
    int _M_timer_id;
    // ---------------------------------------------------------------------------------
    int _M_cached_duration;
    // ---------------------------------------------------------------------------------
    QStringList _M_sources;
    // ---------------------------------------------------------------------------------
};
}
}
#endif // DONTPANICENGINE_H
