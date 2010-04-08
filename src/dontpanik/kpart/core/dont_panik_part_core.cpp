#include "dont_panik_part_core.hpp"
#include "dont_panik_part_core.moc"
// ---------------------------------------------------------------------------------
#include <config.h>
// ---------------------------------------------------------------------------------
//Qt includes
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include "context.h"
#include "desktopnotificationmanager.h"
#include "kmainwidget.h"
#include "kstatus.h"
#include "kdurationstatusupdater.h"
#include "keditactiondialog.h"
#include "kprojectsdialog.h"
#include "ktasksdialog.h"
#include "plannedworkingtimesdialog.h"
#include "statusnotifieritem.h"
#include <KStatusBar>
#include <KAction>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    dont_panik_core::dont_panik_core ( KParts::ReadOnlyPart *gui_client, QWidget *parent )
        : QObject ( parent )        
        , _M_read_write ( false )
        , _M_gui_client ( gui_client )        
        , _M_status (new KStatus ( this ) )
        , _M_status_bar_label ( new KDurationStatusUpdater ( this ) )
        , _M_desktop_notification_manager ( new DesktopNotificationManager ( this ) )
    {
      context()->registerGlobalActions ( gui_client->actionCollection() );
      _M_widget = new KMainWidget ( parent );
      _M_status_bar_label->addTo ( new KParts::StatusBarExtension ( gui_client ) );
      init_statusbar_label();
      init_status_notifier_item ( gui_client->widget() );
      init_desktop_notification_manager();
      connect(context()->timeTracker() , SIGNAL(currentlyActiveActionChanged(dp::Action)), gui_client, SLOT(onCurrentlyActiveActionChanged(dp::Action)));
      connect(_M_widget, SIGNAL(dayViewMode()), gui_client, SLOT(onCurrentlyDisplayingDayView()));
      connect(_M_widget, SIGNAL(reportViewMode()), gui_client, SLOT(onCurrentlyDisplayingReportsView()));
      _M_status->updateAll();
      init_correct_action_states();
    }
    // ---------------------------------------------------------------------------------
    QWidget *dont_panik_core::widget()
    {
      return _M_widget;
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::editProjects()
    {
      KProjectsDialog dlg ( widget() );
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::editTasks()
    {
      KTasksDialog dlg ( widget() );
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::editPlannedWorkingTimes()
    {
      PlannedWorkingTimesDialog dlg ( widget() );
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::addAction()
    {
      KEditActionDialog dlg;
      dlg.setCurrentDay ( context()->currentlySelectedDate() );
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::stopCurrentAction()
    {
      context()->timeTracker()->stopCurrentAction();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::continueAction()
    {
      //context()->timeTracker()->continueLastAction();
      emit continueActionTriggered();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::startNewAction()
    {
      context()->timeTracker()->startNewAction();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::viewDayAction()
    {
      _M_widget->show_dayview();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::viewReportsAction()
    {
      _M_widget->show_reportview();
    }
    // ---------------------------------------------------------------------------------
    bool dont_panik_core::openFile()
    {
      return true;
    }
    // ---------------------------------------------------------------------------------
    bool dont_panik_core::is_read_write() const
    {
      return _M_read_write;
    }
    // ---------------------------------------------------------------------------------
    StatusNotifierItem* dont_panik_core::statusNotifierItem()
    {
      return _M_status_notifier_item;
    }
    // ---------------------------------------------------------------------------------
    // private stuff:
    // ---------------------------------------------------------------------------------
    void dont_panik_core::init_status_notifier_item ( QWidget *parent_widget )
    {
#ifdef DP_BUILD_TRAY_ICON_SUPPORT
      _M_status_notifier_item = new StatusNotifierItem ( this );
      connect ( _M_status, SIGNAL ( currentProjectChanged ( QString ) ), _M_status_notifier_item, SLOT ( onCurrentProjectChanged ( QString ) ) );
      connect ( _M_status, SIGNAL ( todaysDurationChanged ( int ) ), _M_status_notifier_item, SLOT ( onTodaysDurationChanged ( int ) ) );
      connect ( _M_status, SIGNAL ( iconChanged ( QString const& ) ), _M_status_notifier_item, SLOT ( onIconChanged ( QString const& ) ) );
#endif //DP_BUILD_TRAY_ICON_SUPPORT
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::init_statusbar_label()
    {
      connect ( _M_status, SIGNAL ( currentProjectChanged ( QString ) ), _M_status_bar_label, SLOT ( onCurrentProjectChanged ( QString ) ) );
      connect ( _M_status, SIGNAL ( currentlySelectedDaysDurationChanged ( int ) ), _M_status_bar_label, SLOT ( onCurrentlySelectedDaysDurationChanged ( int ) ) );
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::init_desktop_notification_manager()
    {
      _M_desktop_notification_manager->setComponentData(_M_gui_client->componentData());
      connect ( _M_status, SIGNAL ( noJobTrackingsWarning(QString)), _M_desktop_notification_manager, SLOT ( showNoJobTrackingWarning ( QString ) ) );
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::init_correct_action_states()
    {
      context()->globalActions()->action("view_day")->setEnabled(false);
      context()->globalActions()->action("view_reports")->setEnabled(true);
      context()->globalActions()->action("stop_current_action")->setEnabled(context()->timeTracker()->currentlyActiveAction().isActive());
    }
    // ---------------------------------------------------------------------------------
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
