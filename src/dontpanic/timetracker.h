#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include <libdontpanic/defines.hpp>
#include <libdontpanic/action.hpp>
#include <libdontpanic/actiontemplate.hpp>
#include <QObject>

class QUuid;
namespace dp
{
  // ---------------------------------------------------------------------------------
  class TimeTracker: public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      Q_CLASSINFO ( "D-Bus Interface", "org.dontpanic.TimeTracker" )
      // ---------------------------------------------------------------------------------
    signals: 
      void removed(dp::Action);
      void stored(dp::Action);
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TimeTracker ( QObject* parent = 0 );
      // ---------------------------------------------------------------------------------
    public slots:
      // ---------------------------------------------------------------------------------
      void startNewAction();
      // ---------------------------------------------------------------------------------
      void store(Action const&);
      // ---------------------------------------------------------------------------------
      void remove(Action const& );
      // ---------------------------------------------------------------------------------
      void startNewActionFromTemplate ( ActionTemplate const& _template );
      void startNewActionFromTemplate(QUuid const& _template_id);
      // ---------------------------------------------------------------------------------
      void stopCurrentAction();
      // ---------------------------------------------------------------------------------
      void continueLastAction();
      // ---------------------------------------------------------------------------------
      ActionList findAll(QDateTime const& from, QDateTime  const& to);
      // ---------------------------------------------------------------------------------
      private:
      // ---------------------------------------------------------------------------------
      void load_last_action();
      // ---------------------------------------------------------------------------------
      void start_action(Action const& a);
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      Action _M_current_action;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
#endif // TIMETRACKER_H
