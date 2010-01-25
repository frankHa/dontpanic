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
    qDebug() << __FUNCTION__;
    if ( _M_current_action.isValid())
    {
      stopCurrentAction();
    }
    _M_current_action = Action();
    _M_current_action.setStartTime ( QDateTime::currentDateTime().toUTC() );
    persistence().persist ( _M_current_action );
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewActionFrom ( ActionTemplate const& _template )
  {
    qDebug() << __FUNCTION__;
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
  //private stuff:
  // ---------------------------------------------------------------------------------
  void TimeTracker::init()
  {
    _M_current_action = persistence().activeAction();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
