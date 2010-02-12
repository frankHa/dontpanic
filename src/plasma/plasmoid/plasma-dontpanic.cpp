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
    // A small demonstration of the setFailedToLaunch function
} 
 
QGraphicsWidget* PlasmaDontPanic::graphicsWidget()
{
  if(!_M_dialog)
  {
    _M_dialog = new Dialog(this, this);
  }
  return _M_dialog->dialog();
}

void PlasmaDontPanic::toolTipAboutToShow()
{
  Plasma::ToolTipContent toolTip;
  toolTip.setImage(KIcon("dontpanik"));
  toolTip.setMainText("42");
  toolTip.setSubText(i18n("don't panic :)"));
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
     }
   }
 }
#include "plasma-dontpanic.moc"
