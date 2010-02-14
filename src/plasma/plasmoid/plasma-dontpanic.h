#ifndef PLASMA_DP_H
#define PLASMA_DP_H
#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <KIcon>

#include "detail/action.h"
class QSizeF;
class KAction;

namespace Plasma
{
class DataEngine;
}

namespace dp
{
  class ActionTemplate;
  namespace client
  {
    class TimeTracker;
    class ActionTemplateManager;
  }
namespace plasma
{
namespace applet
{
class Dialog;
// Define our plasma Applet
class PlasmaDontPanic : public Plasma::PopupApplet
{
    Q_OBJECT
  signals:
    void currentDurationChanged(int);
    void currentActionChanged(detail::Action const&);
public:
    // Basic Create/Destroy
    PlasmaDontPanic(QObject *parent, const QVariantList &args);
    ~PlasmaDontPanic();

    // The paintInterface procedure paints the applet to screen
//         void paintInterface(QPainter *painter,
//                 const QStyleOptionGraphicsItem *option,
//                 const QRect& contentsRect);
    void init();

    QGraphicsWidget * graphicsWidget();

public slots:

    void toolTipAboutToShow();

    void toolTipHidden();
    void dataUpdated(QString const&,Plasma::DataEngine::Data const&);

  private slots:
    void on_source_added(QString const& source);
    void setup_actions();
    void on_switch_activity_to_triggered(ActionTemplate const& templ);
  public:
    KAction * start_new_action();
    KAction * stop_current_action();
    KAction * resume_last_action();
    KAction * action_for(ActionTemplate const&);
private:
    Plasma::DataEngine *_M_dont_panic_engine;
    Dialog *_M_dialog;
    
    detail::Action _M_current_action;    
    int _M_current_overall_duration;
    KAction *_M_start_new_action;
    KAction *_M_stop_current_action;
    KAction *_M_resume_last_action;
    
    dp::client::TimeTracker *_M_time_tracker;
    dp::client::ActionTemplateManager *_M_action_templates;
};
}
}
}

#endif
