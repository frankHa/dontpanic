#include "dontpanik_part.hpp"

#include "dontpanik_part.moc"

#include "dont_panik_part_core.hpp"
#include <libdontpanic/dbus.hpp>

#include <kaction.h>
#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kfiledialog.h>
#include <kparts/genericfactory.h>
#include <kstandardaction.h>
#include <kshortcut.h>
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

  dp::dbus().register_dp_custom_types();
  QWidget *canvas = new QWidget ( parentWidget );

  _M_core = new dp::core::dont_panik_core ( this, canvas );

  // notify the part that this is our internal widget
  setWidget ( canvas );
  QVBoxLayout *topLayout = new QVBoxLayout ( canvas );

  topLayout->addWidget ( _M_core->widget() );
  
  setup_actions();
  
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

void DontPanikPart::editProjects()
{
  _M_core->editProjects();
}

void DontPanikPart::editTasks()
{
  _M_core->editTasks();
}

void DontPanikPart::stopCurrentAction()
{
  _M_core->stopCurrentAction();
}

void DontPanikPart::continueLastAction()
{
  _M_core->continueLastAction();
}

void DontPanikPart::startNewAction()
{
  _M_core->startNewAction();
}

void DontPanikPart::viewDayAction()
{
  _M_core->viewDayAction();
}

void DontPanikPart::viewReportsAction()
{
  _M_core->viewReportsAction();
}

void DontPanikPart::setup_actions()
{
  KAction *edit_projects = new KAction ( this );
  edit_projects->setText ( i18n ( "Edit Projects" ) );
  actionCollection()->addAction ( "edit_projects", edit_projects );
  connect ( edit_projects, SIGNAL ( triggered() ), this, SLOT ( editProjects() ) );
  
  KAction *edit_tasks = new KAction ( this );
  edit_tasks->setText ( i18n ( "Edit Tasks/Worktypes" ) );
  actionCollection()->addAction ( "edit_tasks", edit_tasks );
  connect ( edit_tasks, SIGNAL ( triggered() ), this, SLOT ( editTasks() ) );
  
  KAction *start_new_action = new KAction(this);
  start_new_action->setText(i18n("Start Action"));
  start_new_action->setShortcut( KShortcut(i18n("Ctrl+S")));
  actionCollection()->addAction ( "start_new_action", start_new_action );
  connect ( start_new_action, SIGNAL ( triggered() ), this, SLOT ( startNewAction() ) );
  
  KAction *stop_current_action = new KAction(this);
  stop_current_action->setText(i18n("Stop current Action"));
  stop_current_action->setShortcut( KShortcut(i18n("Ctrl+T")));
  actionCollection()->addAction ( "stop_current_action", stop_current_action );
  connect ( stop_current_action, SIGNAL ( triggered() ), this, SLOT ( stopCurrentAction() ) );
  
  KAction *continue_last_action = new KAction(this);
  continue_last_action->setText(i18n("Resume the last Action"));
  continue_last_action->setShortcut( KShortcut(i18n("Ctrl+R")));
  actionCollection()->addAction ( "continue_last_action", continue_last_action );
  connect ( continue_last_action, SIGNAL ( triggered() ), this, SLOT ( continueLastAction() ) );
  
  KAction *view_day_action = new KAction(this);
  view_day_action->setText(i18n("Day View"));
  view_day_action->setShortcut( KShortcut(i18n("Ctrl+V, Ctrl+D")));
  actionCollection()->addAction ( "view_day", view_day_action );
  connect ( view_day_action, SIGNAL ( triggered() ), this, SLOT ( viewDayAction() ) );
  
  KAction *view_reports_action = new KAction(this);
  view_reports_action->setText(i18n("Reports View"));
  view_reports_action->setShortcut( KShortcut(i18n("Ctrl+V, Ctrl+R")));
  actionCollection()->addAction ( "view_reports", view_reports_action );
  connect ( view_reports_action, SIGNAL ( triggered() ), this, SLOT ( viewReportsAction() ) );
  
}

