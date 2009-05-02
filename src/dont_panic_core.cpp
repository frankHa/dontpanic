#include "dont_panic_core.hpp"
#include "dont_panic_core.moc"
// ---------------------------------------------------------------------------------
//Qt includes
#include <QWidget>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  dont_panic_core::dont_panic_core ( KXMLGUIClient *gui_client, bool read_write, QWidget *parent )
      : QObject ( parent )
      , _M_read_write ( read_write )
      , _M_gui_client ( gui_client )
  {
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
