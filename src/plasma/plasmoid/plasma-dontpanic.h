#ifndef PLASMA_DP_H
#define PLASMA_DP_H
#include <Plasma/Applet>
#include <Plasma/Svg>
#include <KIcon>

class QSizeF;
 
namespace Plasma
{
  class LineEdit;
  class PushButton;
}
 
// Define our plasma Applet
class PlasmaDontPanic : public Plasma::Applet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        PlasmaDontPanic(QObject *parent, const QVariantList &args);
        ~PlasmaDontPanic();
 
        // The paintInterface procedure paints the applet to screen
//         void paintInterface(QPainter *painter,
//                 const QStyleOptionGraphicsItem *option,
//                 const QRect& contentsRect);
        void init();
 
    private:
        Plasma::Svg m_svg;
        KIcon m_icon;
        Plasma::LineEdit *_M_lineEdit;
        Plasma::PushButton *_M_pushButton;
};
 
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(dontpanic, PlasmaDontPanic)
 
#endif
