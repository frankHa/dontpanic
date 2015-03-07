#include "dontpanik_part.hpp"

#include <dontpanik/defines.hpp>

#include "dont_panik_part_core.hpp"
#include "statusnotifieritem.h"
#include <libdontpanic/dbus.hpp>
#include <libdontpanic/action.hpp>

#include <QAction>
#include <KActionCollection>
#include <QFileDialog>
#include <KAboutData>
#include <KCoreAddons/KPluginFactory>
#include <kstandardaction.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QTextEdit>
#include <QVBoxLayout>

#define DP_KPART_VERSION "0.0.1"
#define DP_KPART_AUTHOR_FH "Frank Habel"
#define DP_KPART_AUTHOR_FH_EMAIL "frank@bugplasma.de"

 K_PLUGIN_FACTORY(DontPanikPartFactory,
                  registerPlugin<DontPanikPart>();
                 )
#include "dontpanik_part.moc"

DontPanikPart::DontPanikPart ( QWidget *parentWidget, QObject *parent, const QVariantList & /*args*/ )
    : KParts::ReadOnlyPart ( parent )
{
  //KGlobal::locale()->insertCatalog("dontpanic");
  // we need an instance
  //setComponentData ( DontPanikPartFactory::);

  dp::dbus().register_dp_custom_types();
  QWidget *canvas = new QWidget ( parentWidget );

  setup_actions();
  setWidget ( canvas );
  _M_core = new dp::core::dont_panik_core ( this, canvas );
  _M_core->statusNotifierItem()->setAssociatedWidget(parentWidget);
  // notify the part that this is our internal widget
  
  QVBoxLayout *topLayout = new QVBoxLayout ( canvas );

  topLayout->addWidget ( _M_core->widget() );
  
  // set our XML-UI resource file
  setXMLFile ( "dontpanik_part.rc" );
}

DontPanikPart::~DontPanikPart()
{
}

KAboutData *DontPanikPart::createAboutData()
{
  // the non-i18n name here must be the same as the directory in
  // which the part's rc file is installed ('partrcdir' in the
  // Makefile)
  KAboutData *aboutData = new KAboutData ( "dontpanikpart", i18n ( "DontPanikPart" ), DP_KPART_VERSION );
  aboutData->addAuthor ( i18n ( DP_KPART_AUTHOR_FH ), QString(), DP_KPART_AUTHOR_FH_EMAIL );
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

void DontPanikPart::editPlannedWorkingTimes()
{
  _M_core->editPlannedWorkingTimes();
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

void DontPanikPart::onCurrentlyActiveActionChanged(const dp::Action& a)
{
  if(a.isActive())
  {
    emit stateChanged("has_active_action");
  }
  else
  {
    emit stateChanged("has_active_action", StateReverse);
  }  
}

void DontPanikPart::onCurrentlyDisplayingDayView()
{
  emit stateChanged("displaying_view_day");
  emit stateChanged("displaying_view_reports", StateReverse);
}

void DontPanikPart::onCurrentlyDisplayingReportsView()
{
  emit stateChanged("displaying_view_day", StateReverse);
  emit stateChanged("displaying_view_reports");
}

void DontPanikPart::setup_actions()
{
  QAction *edit_projects = new QAction ( this );
  edit_projects->setText ( i18n ( "Edit Projects" ) );
  edit_projects->setIcon(QIcon::fromTheme("applications-engineering"));
  actionCollection()->addAction ( "edit_projects", edit_projects );
  connect ( edit_projects, SIGNAL ( triggered() ), this, SLOT ( editProjects() ) );
  
  QAction *edit_tasks = new QAction ( this );
  edit_tasks->setText ( i18n ( "Edit Tasks/Worktypes" ) );
  edit_tasks->setIcon(QIcon::fromTheme("view-pim-tasks"));
  actionCollection()->addAction ( "edit_tasks", edit_tasks );
  connect ( edit_tasks, SIGNAL ( triggered() ), this, SLOT ( editTasks() ) );
  
  QAction *edit_planned_working_times = new QAction ( this );
  edit_planned_working_times->setText ( i18n ( "Edit Planned Working Times" ) );
  edit_planned_working_times->setIcon(QIcon::fromTheme("preferences-system-time"));
  actionCollection()->addAction ( "edit_planned_working_times", edit_planned_working_times );
  connect ( edit_planned_working_times, SIGNAL ( triggered() ), this, SLOT ( editPlannedWorkingTimes() ) );
  
  QAction *add_new_action = new QAction(this);
  add_new_action->setText(i18n("Add &new Action"));
  add_new_action->setIcon(QIcon::fromTheme("document-new"));
  actionCollection()->addAction ( "add_new_action", add_new_action );
  actionCollection()->setDefaultShortcut(add_new_action, QKeySequence("Ctrl+N"));
  connect ( add_new_action, SIGNAL ( triggered() ), this, SLOT ( addAction() ) );
  
  QAction *start_new_action = new QAction(this);
  start_new_action->setText(i18n("Start Action"));
  start_new_action->setIcon(QIcon::fromTheme("media-playback-start"));
  actionCollection()->addAction ( "start_new_action", start_new_action );
  actionCollection()->setDefaultShortcut(start_new_action, QKeySequence("Ctrl+S"));
  connect ( start_new_action, SIGNAL ( triggered() ), this, SLOT ( startNewAction() ) );
  
  QAction *stop_current_action = new QAction(this);
  stop_current_action->setText(i18n("Stop current Action"));
  stop_current_action->setIcon(QIcon::fromTheme("media-playback-stop"));
  actionCollection()->addAction ( "stop_current_action", stop_current_action );
  actionCollection()->setDefaultShortcut(stop_current_action, QKeySequence("Ctrl+T"));
  connect ( stop_current_action, SIGNAL ( triggered() ), this, SLOT ( stopCurrentAction() ) );
  
  QAction *continue_action = new QAction(this);
  continue_action->setText(i18n("Resume Action"));
  continue_action->setIcon(QIcon::fromTheme("media-seek-forward"));
  actionCollection()->addAction ( "continue_action", continue_action );
  actionCollection()->setDefaultShortcut(continue_action, QKeySequence("Ctrl+R"));
  connect ( continue_action, SIGNAL ( triggered() ), this, SLOT ( continueAction() ) );
  
  QAction *view_day_action = new QAction(this);
  view_day_action->setText(i18n("Day View"));
  view_day_action->setIcon(QIcon::fromTheme("view-pim-calendar"));
  actionCollection()->addAction ( "view_day", view_day_action );
  actionCollection()->setDefaultShortcut(view_day_action, QKeySequence("Ctrl+V, Ctrl+D"));
  connect ( view_day_action, SIGNAL ( triggered() ), this, SLOT ( viewDayAction() ) );
  
  QAction *view_reports_action = new QAction(this);
  view_reports_action->setText(i18n("Reports View"));
  view_reports_action->setIcon(QIcon::fromTheme("view-calendar-list"));
  actionCollection()->addAction ( "view_reports", view_reports_action );
  actionCollection()->setDefaultShortcut(view_reports_action, QKeySequence("Ctrl+V, Ctrl+R"));
  connect ( view_reports_action, SIGNAL ( triggered() ), this, SLOT ( viewReportsAction() ) );
  
}

