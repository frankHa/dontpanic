#include "plasma-dontpanic.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <Plasma/LineEdit>
#include <Plasma/PushButton>
#include <plasma/svg.h>
#include <plasma/theme.h>
 
 
PlasmaDontPanic::PlasmaDontPanic(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
    m_svg(this)
    ,m_icon("dontpanik")
    , _M_lineEdit(0)
    , _M_pushButton(0)
{
    m_svg.setImagePath("widgets/background");
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    resize(200, 200);
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
 
    // A small demonstration of the setFailedToLaunch function
    if (m_icon.isNull()) {
        setFailedToLaunch(true, "No world to say hello");
    }
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);
    layout->setOrientation(Qt::Vertical); //so widgets will be stacked up/down
    
    _M_lineEdit = new Plasma::LineEdit(this);
    _M_lineEdit->setText("Hey! This is a Plasma line edit.");
    
    _M_pushButton = new Plasma::PushButton(this);
    _M_pushButton->setText("Whoa! This is a Plasma pushbutton.");
    _M_pushButton->setIcon(m_icon);
    layout->addItem(_M_lineEdit);
    layout->addItem(_M_pushButton);
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
 
#include "plasma-dontpanic.moc"
