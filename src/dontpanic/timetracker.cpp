#include "timetracker.h"
#include "libdontpanic/action.hpp"
#include "persistencebackend.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  TimeTracker::TimeTracker ( QObject *parent )
      : QObject ( parent )
  {
    init();
  }
  // ---------------------------------------------------------------------------------
  void TimeTracker::startNewAction()
  {
    qDebug() << __FUNCTION__;
    if ( _M_current_action.get() != 0 )
    {
      stopCurrentAction();
    }
    _M_current_action.reset ( new Action() );
    _M_current_action->setStartTime ( QDateTime::currentDateTime().toUTC() );
    persistence().persist ( *_M_current_action );
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
    if ( _M_current_action.get() == 0 )
    {
      return;
    }
    _M_current_action->setEndTime ( QDateTime::currentDateTime().toUTC() );
    persistence().persist ( *_M_current_action );
    _M_current_action.reset();
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
