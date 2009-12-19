#include "dontpanik_part.hpp"

#include "dontpanik_part.moc"

#include "dont_panik_part_core.hpp"

#include <kaction.h>
#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kfiledialog.h>
#include <kparts/genericfactory.h>
#include <kstandardaction.h>
#include <kdebug.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QTextEdit>
#include <QVBoxLayout>

#define DP_KPART_VERSION "0.0.1"
#define DP_KPART_AUTHOR_FH "Frank Habel"
#define DP_KPART_AUTHOR_FH_EMAIL "frank@bugplasma.de"

typedef KParts::GenericFactory<DontPanikPart> DontPanikPartFactory;
K_EXPORT_COMPONENT_FACTORY ( dontpanikpart, DontPanikPartFactory )

DontPanikPart::DontPanikPart ( QWidget *parentWidget, QObject *parent, const QStringList & /*args*/ )
    : KParts::ReadOnlyPart ( parent )
{
  // we need an instance
  setComponentData ( DontPanikPartFactory::componentData() );

  QWidget *canvas = new QWidget ( parentWidget );

  _M_core = new dp::dont_panik_core ( this, canvas );

  // notify the part that this is our internal widget
  setWidget ( canvas );
  QVBoxLayout *topLayout = new QVBoxLayout ( canvas );

  topLayout->addWidget ( _M_core->widget() );
  // create our actions
  //KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
  //save = KStandardAction::save(this, SLOT(save()), actionCollection());
  KAction *edit_projects = new KAction ( this );
  edit_projects->setText ( i18n("Edit Projects") );
  actionCollection()->addAction ("edit_projects", edit_projects );

  KAction *edit_worktypes = new KAction ( this );
  edit_worktypes->setText ( i18n("Edit Worktypes") );
  actionCollection()->addAction ("edit_worktypes", edit_worktypes );

  // set our XML-UI resource file
  setXMLFile ( "dontpanik_part.rc" );

  // we are read-write by default
  //setReadWrite(true);

  // we are not modified since we haven't done anything yet
  //setModified(false);
}

DontPanikPart::~DontPanikPart()
{
}

//void DontPanikPart::setReadWrite(bool rw)
//{
//    _M_core->set_read_write(rw);
//    ReadWritePart::setReadWrite(rw);
//}

//void DontPanikPart::setModified(bool modified)
//{
// get a handle on our Save action and make sure it is valid
//    if (!save)
//        return;

// if so, we either enable or disable it based on the current
// state
//    if (modified)
//        save->setEnabled(true);
//    else
//        save->setEnabled(false);

// in any event, we want our parent to do it's thing
//    ReadWritePart::setModified(modified);
//}

KAboutData *DontPanikPart::createAboutData()
{
  // the non-i18n name here must be the same as the directory in
  // which the part's rc file is installed ('partrcdir' in the
  // Makefile)
  KAboutData *aboutData = new KAboutData ( "dontpanikpart", 0, ki18n ( "DontPanikPart" ), DP_KPART_VERSION );
  aboutData->addAuthor ( ki18n ( DP_KPART_AUTHOR_FH ), KLocalizedString(), DP_KPART_AUTHOR_FH_EMAIL );
  return aboutData;
}

bool DontPanikPart::openFile()
{
  return _M_core->openFile();
}

bool DontPanikPart::saveFile()
{
  return _M_core->saveFile();
}

//void DontPanikPart::fileSaveAs()
//{
// this slot is called whenever the File->Save As menu is selected,
//    QString file_name = KFileDialog::getSaveFileName();
//    if (file_name.isEmpty() == false)
//        saveAs(file_name);
//}

