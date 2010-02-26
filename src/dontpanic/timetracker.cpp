#include "timetracker.h"
#include "libdontpanic/action.hpp"
#include "persistencebackend.hpp"
#include <KDebug>
// ---------------------------------------------------------------------------------
namespace dp
{
  
  // ---------------------------------------------------------------------------------
  TimeTracker::TimeTracker ( QObject *parent )
      : QObject ( parent )
      , _M_current_action(NullAction())
  {
    load_last_action();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewAction()
  {
    Action a;
     start_action(a);
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::remove(Action const& a)
  {
    if(_M_current_action == a)
    {
      stopCurrentAction();
    }
    if(persistence().remove(a).was_successful())
    {
      emit removed(a);
    }
    load_last_action();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::store(Action const& a)
  {
    if(_M_current_action == a){_M_current_action = a;}
    if(persistence().persist(a).was_successful())
    {
      emit stored(a);
    }
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewActionFromTemplate ( ActionTemplate const& _template )
  {
    qDebug() << __FUNCTION__;
    Action a;
    a.setProject(_template.project());
    a.setTask(_template.task());
    a.setName(_template.name());
    start_action(a);
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewActionFromTemplate ( Uuid const& _template_id )
  {
    ActionTemplate templ(_template_id);
    if(persistence().load(templ).has_failed())
    {
      kWarning()<<"unable to find template id :" << _template_id.toString();
      kWarning()<<"not starting a new action here";
      return;
    }
    startNewActionFromTemplate(templ);
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::stopCurrentAction()
  {
    kDebug() <<"";
    if ( !_M_current_action.isActive() )
    {
      kDebug()<<"current action not active->doing nothing...";
      return;
    }
    _M_current_action.setEndTime ( QDateTime::currentDateTime() );
    store(_M_current_action);
    kDebug()<<"current action stopped";
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::continueLastAction()
  {
    if(!_M_current_action.isValid()){return;}
    if(_M_current_action.isActive()){return;}
    _M_current_action.setEndTime(QDateTime());
    store(_M_current_action);
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::continueAction(Action const& a)
  {
    if(a == _M_current_action) {continueLastAction(); return;}
    Action newAction;
    newAction.setCollaborationType(a.collaborationType());
    newAction.setComment(a.comment());
    newAction.setName(a.name());
    newAction.setProject(a.project());
    newAction.setTask(a.task());
    start_action(newAction);
  }
  // ---------------------------------------------------------------------------------
  ActionList TimeTracker::findAll(QDateTime const& from, QDateTime const& to)
  {
    ActionList list;
    persistence().findAll(list, from, to);
    return list;
  }
  // ---------------------------------------------------------------------------------
  Action TimeTracker::findCurrentlyActiveAction() const
  {
    if(_M_current_action.isActive())return _M_current_action;
    return NullAction();
  }
  // ---------------------------------------------------------------------------------
  bool TimeTracker::hasActionsFor(QDate const& date)
  {
    return persistence().hasActionsFor(date);
  }
  // ---------------------------------------------------------------------------------
  //private stuff:
  // ---------------------------------------------------------------------------------
  void TimeTracker::load_last_action()
  {
    _M_current_action = persistence().lastAction();
    kDebug()<<"last action:"<<_M_current_action.id().toString()
    <<", starting:"<< _M_current_action.startTime()<<", ended: "<<_M_current_action.endTime()
    <<", is Active:"<<_M_current_action.isActive();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::start_action(Action const& _a)
  {
    kDebug() << __FUNCTION__;
    if ( _M_current_action.isValid())
    {
      stopCurrentAction();
    }
    _M_current_action = _a;
    _M_current_action.setStartTime ( QDateTime::currentDateTime() );
    store(_M_current_action);
  }  
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
