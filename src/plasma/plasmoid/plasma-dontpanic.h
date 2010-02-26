#ifndef PLASMA_DP_H
#define PLASMA_DP_H
#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <KIcon>

#include "detail/action.h"
#include "detail/favorite.h"
#include <libdontpanic/actiontemplate.hpp>
class QSizeF;
class KAction;

namespace Plasma
{
class DataEngine;
}

namespace dp
{
  namespace client
  {
    class TimeTracker;
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
    void favorite_added(detail::Favorite const& );
    void favorite_removed(detail::Favorite const& );
    void favorite_updated(detail::Favorite const& );
    void icon_updated(QString const&);
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
    void on_source_removed(QString const& source);
    void setup_actions();
    void on_switch_activity_to_triggered(detail::Favorite const& templ);
  public:
    KAction * start_new_action();
    KAction * stop_current_action();
    KAction * resume_last_action();
    KAction * action_for(detail::Favorite const&);
    detail::FavoriteList favorites() const;
    QString icon() const;
  private:
    void store_in_favorites(detail::Favorite const&);
  private slots:
    void updateIcon();
private:
    Plasma::DataEngine *_M_dont_panic_engine;
    Dialog *_M_dialog;
    
    detail::Action _M_current_action;    
    int _M_current_overall_duration;
    KAction *_M_start_new_action;
    KAction *_M_stop_current_action;
    KAction *_M_resume_last_action;
    
    QString _M_icon;
    dp::client::TimeTracker *_M_time_tracker;
    
    detail::FavoriteList _M_favorites;
};
}
}
}

#endif
