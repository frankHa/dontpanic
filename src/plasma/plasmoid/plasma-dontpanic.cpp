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

#include "dialog.h"
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
      QString tooltip = i18n("Current Don't Panik action: \nProject:\t\t%1\nTask:\t\t%2\nRunning since:\t%3\nCurrent duration:\t%4")
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
  }
}

void PlasmaDontPanic::on_source_added(QString const& src)
{
  _M_dont_panic_engine->connectSource(src,this);
}
}
}
}
#include "plasma-dontpanic.moc"
