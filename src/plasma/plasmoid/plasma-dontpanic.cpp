#include "plasma-dontpanic.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <Plasma/ToolTipManager>
#include <Plasma/LineEdit>
#include <Plasma/PushButton>
#include <plasma/svg.h>
#include <plasma/theme.h>
#include <Plasma/DataEngine>

#include <libdontpanic/durationformatter.h>
#include <libdontpanic_client/timetracker.h>
#include <libdontpanic_client/actiontemplatemanager.h>
#include <KAction>
#include <KIcon>
#include <QMenu>

#include "dialog.h"
#include "detail/actiontemplateaction.h"

K_EXPORT_PLASMA_APPLET(dontpanic, dp::plasma::applet::PlasmaDontPanic)
namespace dp
{
namespace plasma
{
namespace applet
{

PlasmaDontPanic::PlasmaDontPanic(QObject *parent, const QVariantList &args)
        : Plasma::PopupApplet(parent, args)
        , _M_dialog(0)
        , _M_current_overall_duration(0)
{
    setPopupIcon("dontpanik");
}


PlasmaDontPanic::~PlasmaDontPanic()
{
  if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

void PlasmaDontPanic::init()
{
    _M_time_tracker = new dp::client::TimeTracker(this);
    _M_action_templates = new dp::client::ActionTemplateManager(this);
    setup_actions();
    Plasma::ToolTipManager::self()->registerWidget(this);
    _M_dont_panic_engine = dataEngine("dontpanic");
    if (_M_dont_panic_engine == 0 || !_M_dont_panic_engine->isValid())
    {
        setFailedToLaunch(true, "Unable to find the dontpanic data engine");
        return;
    }
    _M_dont_panic_engine->connectSource("dp/today", this);
    _M_dont_panic_engine->connectSource("dp/current activity", this);
    connect(_M_dont_panic_engine, SIGNAL(sourceAdded(QString const&)), this, SLOT(on_source_added(QString const&)));
}

QGraphicsWidget* PlasmaDontPanic::graphicsWidget()
{
    if (!_M_dialog)
    {
        _M_dialog = new Dialog(this, this);
    }
    return _M_dialog->dialog();
}

void PlasmaDontPanic::toolTipAboutToShow()
{
    Plasma::ToolTipContent toolTip;
    toolTip.setImage(KIcon("dontpanik"));
    toolTip.setMainText(duration_formatter().format(_M_current_overall_duration));
    if(!_M_current_action.active)
    {
      toolTip.setSubText(i18n("There is currently no active Don't Panic action..."));
    } 
    else
    {
      QString tooltip = i18n("Current activity:<br/>%1/%2<br/>Running since: %3 (%4h)")
      .arg(_M_current_action.project)
      .arg(_M_current_action.task)
      .arg(_M_current_action.start.time().toString(Qt::SystemLocaleShortDate))
      .arg(duration_formatter().format(_M_current_action.duration));
      toolTip.setSubText(tooltip);
    }
    Plasma::ToolTipManager::self()->setContent(this, toolTip);
}

void PlasmaDontPanic::toolTipHidden()
{
    Plasma::ToolTipManager::self()->clearContent(this);
}
// void PlasmaDontPanic::paintInterface(QPainter *p,
//         const QStyleOptionGraphicsItem *option, const QRect &contentsRect)
// {
//     p->setRenderHint(QPainter::SmoothPixmapTransform);
//     p->setRenderHint(QPainter::Antialiasing);
//
//     // Now we draw the applet, starting with our svg
//     m_svg.resize((int)contentsRect.width(), (int)contentsRect.height());
//     m_svg.paint(p, (int)contentsRect.left(), (int)contentsRect.top());
//
//     // We place the icon and text
//     p->drawPixmap(7, 0, m_icon.pixmap((int)contentsRect.width(),(int)contentsRect.width()-14));
//     p->save();
//     p->setPen(Qt::white);
//     p->drawText(contentsRect,
//                 Qt::AlignBottom | Qt::AlignHCenter,
//                 "Hello Don't Panic!");
//     p->restore();
// }

void PlasmaDontPanic::dataUpdated(QString const&source,Plasma::DataEngine::Data const&data)
{
  if(source == "dp/today")
  {
    _M_current_overall_duration = data.constFind("Time").value().toInt();
    emit currentDurationChanged(_M_current_overall_duration);
  }
  if(source == "dp/current activity")
  {
    _M_current_action.active = data.constFind("active").value().toBool();
    if(_M_current_action.active)
    {
      _M_current_action.project = data.constFind("project").value().toString();
      _M_current_action.task = data.constFind("task").value().toString();
      _M_current_action.start = data.constFind("start").value().toDateTime();
      _M_current_action.duration = data.constFind("duration").value().toInt();
    }    
    emit currentActionChanged(_M_current_action);
  }
}

void PlasmaDontPanic::on_source_added(QString const& src)
{
  _M_dont_panic_engine->connectSource(src,this);
}

void PlasmaDontPanic::setup_actions()
{
  _M_start_new_action = new KAction(this);
  //start_new_action->setText(i18n("Start Action"));
  _M_start_new_action->setIcon(KIcon("media-playback-start"));
  _M_start_new_action->setShortcut( KShortcut(i18n("Ctrl+S")));
  connect(_M_start_new_action, SIGNAL(triggered()), _M_time_tracker, SLOT(startNewAction()));
  
  
  _M_stop_current_action = new KAction(this);
  _M_stop_current_action->setIcon(KIcon("media-playback-stop"));
  _M_stop_current_action->setShortcut( KShortcut(i18n("Ctrl+T")));
  connect(_M_stop_current_action, SIGNAL(triggered()), _M_time_tracker, SLOT(stopCurrentAction()));
  
  _M_resume_last_action = new KAction(this);
  _M_resume_last_action->setIcon(KIcon("media-seek-forward"));
  _M_resume_last_action->setShortcut( KShortcut(i18n("Ctrl+R")));
  connect(_M_resume_last_action, SIGNAL(triggered()), _M_time_tracker, SLOT(continueLastAction()));
}

KAction * PlasmaDontPanic::start_new_action()
{
  return _M_start_new_action;
}
KAction * PlasmaDontPanic::stop_current_action()
{
  return _M_stop_current_action;
}
KAction * PlasmaDontPanic::resume_last_action()
{
  return _M_resume_last_action;
}

KAction* PlasmaDontPanic::action_for(ActionTemplate const& templ)
{
  detail::ActionTemplateAction *action = new detail::ActionTemplateAction(this);
  action->setActionTemplate(templ);
  connect(action, SIGNAL(triggered(ActionTemplate)), this, SLOT(on_switch_activity_to_triggered(ActionTemplate)));
  return action;
}

void PlasmaDontPanic::on_switch_activity_to_triggered(const ActionTemplate& templ)
{
  _M_time_tracker->startActionFromTemplate(templ);
}

TemplateList PlasmaDontPanic::favorites()
{
  return _M_action_templates->allActionTemplates();
}


}
}
}
#include "plasma-dontpanic.moc"
