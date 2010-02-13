#ifndef PLASMA_DP_H
#define PLASMA_DP_H
#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <KIcon>

class QSizeF;

namespace Plasma
{
class DataEngine;
}

namespace dp
{
namespace plasma
{
namespace applet
{
class Dialog;
// Define our plasma Applet
class PlasmaDontPanic : public Plasma::PopupApplet
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

    QGraphicsWidget * graphicsWidget();

public slots:

    void toolTipAboutToShow();

    void toolTipHidden();
    void dataUpdated(QString const&,Plasma::DataEngine::Data const&);

  private slots:
    void on_source_added(QString const& source);
private:
    Plasma::DataEngine *_M_dont_panic_engine;
    Dialog *_M_dialog;
    
    struct Action
    {
      Action():active(false), project(""), task(""), start(), duration(0){}
      bool active;
      QString project;
      QString task;
      QDateTime start;
      int duration;
    } _M_current_action;
    
    int _M_current_overall_duration;
    
};
}
}
}

#endif
