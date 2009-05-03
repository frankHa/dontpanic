#include "dont_panik_part_core.hpp"
#include "dont_panik_part_core.moc"
// ---------------------------------------------------------------------------------
//Qt includes
#include <QTextEdit>
#include <QTextStream>
#include <QFile>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  dont_panic_core::dont_panic_core ( KXMLGUIClient *gui_client, bool read_write, QWidget *parent )
      : QObject ( parent )
      , _M_read_write ( read_write )
      , _M_gui_client ( gui_client )
  {
    _M_widget = new QTextEdit ( parent );
  }
  // ---------------------------------------------------------------------------------
  QWidget *dont_panic_core::widget()
  {
    return _M_widget;
  }
  // ---------------------------------------------------------------------------------
  bool dont_panic_core::openFile()
  {
    // m_file is always local so we can use QFile on it
    QFile file ( "m_file" );
    if ( !file.open ( QIODevice::ReadOnly | QIODevice::Text ) )
      return false;

    // our example widget is text-based, so we use QTextStream instead
    // of a raw QDataStream
    QTextStream stream ( &file );
    QString str;
    while ( !stream.atEnd() )
      str += stream.readLine() + "\n";

    file.close();

    // now that we have the entire file, display it
    _M_widget->setPlainText ( str );

    // just for fun, set the status bar
    //emit setStatusBarText( m_url.prettyUrl() );

    return true;
  }
  // ---------------------------------------------------------------------------------
  bool dont_panic_core::saveFile()
  {
    // if we aren't read-write, return immediately
    if ( is_read_write() == false )
      return false;

    // m_file is always local, so we use QFile
    QFile file ( "m_file" );
    if ( !file.open ( QIODevice::ReadOnly | QIODevice::Text ) )
      return false;

    // use QTextStream to dump the text to the file
    QTextStream stream ( &file );
    stream << _M_widget->document();

    file.close();

    return true;
  }
  // ---------------------------------------------------------------------------------
  bool dont_panic_core::is_read_write() const
  {
    return _M_read_write;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
