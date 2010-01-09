#include "dont_panik_part_core.hpp"
#include "dont_panik_part_core.moc"
// ---------------------------------------------------------------------------------
//Qt includes
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
#include "kmainwidget.h"
#include "kprojectsdialog.h"
#include "ktasksdialog.h"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace core
  {
    // ---------------------------------------------------------------------------------
    dont_panik_core::dont_panik_core ( KXMLGUIClient *gui_client, QWidget *parent )
        : QObject ( parent )
        , _M_read_write ( false )
        , _M_gui_client ( gui_client )
    {
      _M_widget = new KMainWidget ( parent );
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
