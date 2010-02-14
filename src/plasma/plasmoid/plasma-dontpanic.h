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
  public:
    KAction * start_new_action();
    KAction * stop_current_action();
    KAction * resume_last_action();
private:
    Plasma::DataEngine *_M_dont_panic_engine;
    Dialog *_M_dialog;
    
    detail::Action _M_current_action;    
    int _M_current_overall_duration;
    KAction *_M_start_new_action;
    KAction *_M_stop_current_action;
    KAction *_M_resume_last_action;
    
};
}
}
}

#endif
