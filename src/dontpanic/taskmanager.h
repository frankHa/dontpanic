#ifndef DP_TASKMANAGER_H
#define DP_TASKMANAGER_H
#include <libdontpanic/defines.hpp>
#include <libdontpanic/task.hpp>
#include <QObject>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class TaskManager
        : public QObject
  {
      // ---------------------------------------------------------------------------------
      Q_OBJECT
      Q_CLASSINFO ( "D-Bus Interface", "org.dontpanic.TaskManager" )
      // ---------------------------------------------------------------------------------
    signals:
      void removed ( dp::Task );
      void stored ( dp::Task );
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TaskManager ( QObject *parent = 0 );
      // ---------------------------------------------------------------------------------
    public slots:
      // ---------------------------------------------------------------------------------
      Task load ( Uuid const& );
      // ---------------------------------------------------------------------------------
      void store ( Task const& p );
      // ---------------------------------------------------------------------------------
      void remove ( Task const& p );
      // ---------------------------------------------------------------------------------
      TaskList findAll();
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif // DP_TASKMANAGER_H
