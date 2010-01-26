#include "timetracker.h"
#include "libdontpanic/action.hpp"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  TimeTracker::TimeTracker ( QObject *parent )
      : QObject ( parent )
      , _M_current_action(NullAction())
  {
    init();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewAction()
  {
     start_action(Action());
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewActionFromTemplate ( ActionTemplate const& _template )
  {
    qDebug() << __FUNCTION__;
    Action a;
    a.setProject(_template.project());
    a.setTask(_template.task());
    start_action(a);
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewActionFromTemplate ( QUuid const& _template_id )
  {
    qDebug() << __FUNCTION__;
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::stopCurrentAction()
  {
    qDebug() << __FUNCTION__;
    if ( !_M_current_action.isValid() )
    {
      return;
    }
    _M_current_action.setEndTime ( QDateTime::currentDateTime().toUTC() );
    persistence().persist ( _M_current_action );
    _M_current_action = NullAction();
  }
  // ---------------------------------------------------------------------------------
  ActionList TimeTracker::findAll(QDateTime const& from, QDateTime const& to)
  {
    ActionList list;
    persistence().findAll(list, from, to);
    return list;
  }
  // ---------------------------------------------------------------------------------
  //private stuff:
  // ---------------------------------------------------------------------------------
  void TimeTracker::init()
  {
    _M_current_action = persistence().activeAction();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::start_action(Action const& _a)
  {
    qDebug() << __FUNCTION__;
    if ( _M_current_action.isValid())
    {
      stopCurrentAction();
    }
    _M_current_action = _a;
    _M_current_action.setStartTime ( QDateTime::currentDateTime().toUTC() );
    persistence().persist ( _M_current_action );
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
