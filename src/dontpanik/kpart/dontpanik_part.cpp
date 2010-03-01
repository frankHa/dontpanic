#include "dontpanik_part.hpp"

#include "dontpanik_part.moc"
#include <config.h>

#include "dont_panik_part_core.hpp"
#include "statusnotifieritem.h"
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
  KGlobal::locale()->insertCatalog("dontpanik");
  // we need an instance
  setComponentData ( DontPanikPartFactory::componentData() );

  dp::dbus().register_dp_custom_types();
  QWidget *canvas = new QWidget ( parentWidget );

  setup_actions();
  setWidget ( canvas );
  _M_core = new dp::core::dont_panik_core ( this, canvas );
  #ifdef DP_BUILD_TRAY_ICON_SUPPORT
  _M_core->statusNotifierItem()->setAssociatedWidget(parentWidget);
  #endif //DP_BUILD_TRAY_ICON_SUPPORT
  // notify the part that this is our internal widget
  
  QVBoxLayout *topLayout = new QVBoxLayout ( canvas );

  topLayout->addWidget ( _M_core->widget() );
  
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

void DontPanikPart::addAction()
{
  _M_core->addAction();
}

void DontPanikPart::stopCurrentAction()
{
  _M_core->stopCurrentAction();
}

void DontPanikPart::continueAction()
{
  _M_core->continueAction();
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
  edit_projects->setIcon(KIcon("applications-engineering"));
  actionCollection()->addAction ( "edit_projects", edit_projects );
  connect ( edit_projects, SIGNAL ( triggered() ), this, SLOT ( editProjects() ) );
  
  KAction *edit_tasks = new KAction ( this );
  edit_tasks->setText ( i18n ( "Edit Tasks/Worktypes" ) );
  edit_tasks->setIcon(KIcon("view-pim-tasks"));
  actionCollection()->addAction ( "edit_tasks", edit_tasks );
  connect ( edit_tasks, SIGNAL ( triggered() ), this, SLOT ( editTasks() ) );
  
  KAction *add_action = new KAction(this);
  add_action->setText(i18n("Add Action"));
  add_action->setIcon(KIcon("document-new"));
  add_action->setShortcut( KShortcut("Ctrl+A"));
  actionCollection()->addAction ( "add_action", add_action );
  connect ( add_action, SIGNAL ( triggered() ), this, SLOT ( addAction() ) );
  
  KAction *start_new_action = new KAction(this);
  start_new_action->setText(i18n("Start Action"));
  start_new_action->setIcon(KIcon("media-playback-start"));
  start_new_action->setShortcut( KShortcut("Ctrl+S"));
  actionCollection()->addAction ( "start_new_action", start_new_action );
  connect ( start_new_action, SIGNAL ( triggered() ), this, SLOT ( startNewAction() ) );
  
  KAction *stop_current_action = new KAction(this);
  stop_current_action->setText(i18n("Stop current Action"));
  stop_current_action->setIcon(KIcon("media-playback-stop"));
  stop_current_action->setShortcut( KShortcut("Ctrl+T"));
  actionCollection()->addAction ( "stop_current_action", stop_current_action );
  connect ( stop_current_action, SIGNAL ( triggered() ), this, SLOT ( stopCurrentAction() ) );
  
  KAction *continue_action = new KAction(this);
  continue_action->setText(i18n("Resume Action"));
  continue_action->setIcon(KIcon("media-seek-forward"));
  continue_action->setShortcut( KShortcut("Ctrl+R"));
  actionCollection()->addAction ( "continue_action", continue_action );
  connect ( continue_action, SIGNAL ( triggered() ), this, SLOT ( continueAction() ) );
  
  KAction *view_day_action = new KAction(this);
  view_day_action->setText(i18n("Day View"));
  view_day_action->setIcon(KIcon("view-pim-calendar"));
  view_day_action->setShortcut( KShortcut("Ctrl+V, Ctrl+D"));
  actionCollection()->addAction ( "view_day", view_day_action );
  connect ( view_day_action, SIGNAL ( triggered() ), this, SLOT ( viewDayAction() ) );
  
  KAction *view_reports_action = new KAction(this);
  view_reports_action->setText(i18n("Reports View"));
  view_reports_action->setIcon(KIcon("view-calendar-list"));
  view_reports_action->setShortcut( KShortcut("Ctrl+V, Ctrl+R"));
  actionCollection()->addAction ( "view_reports", view_reports_action );
  connect ( view_reports_action, SIGNAL ( triggered() ), this, SLOT ( viewReportsAction() ) );
  
}

