#include "dont_panik_part_core.hpp"
#include "dont_panik_part_core.moc"
// ---------------------------------------------------------------------------------
//Qt includes
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include "context.h"
#include "kmainwidget.h"
#include "keditactiondialog.h"
#include "kprojectsdialog.h"
#include "ktasksdialog.h"
#include <KStatusBar>
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
    {
      _M_widget = new KMainWidget ( parent, new KParts::StatusBarExtension(gui_client) );
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
    void dont_panik_core::addAction()
    {
      KEditActionDialog dlg;
      dlg.setCurrentDay(context()->currentDate());
      dlg.exec();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::stopCurrentAction()
    {
      context()->timeTracker()->stopCurrentAction();
    }
    // ---------------------------------------------------------------------------------
    void dont_panik_core::continueLastAction()
    {
      context()->timeTracker()->continueLastAction();
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
  }//core
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
