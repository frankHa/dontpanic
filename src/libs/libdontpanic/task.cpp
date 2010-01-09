#include "libdontpanic/task.hpp"

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Task::Task()
      : _M_id ( QUuid::createUuid() )
      , _M_name ( "" )
      , _M_solo_effort ( true )
      , _M_chargeable ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  Task::Task(QString const& name)
      : _M_id ( QUuid::createUuid() )
      , _M_name ( name )
      , _M_solo_effort ( true )
      , _M_chargeable ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  Task::Task ( QUuid const& id )
      : _M_id ( id )
      , _M_name ( "" )
      , _M_solo_effort ( true )
      , _M_chargeable ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  QUuid const& Task::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString const& Task::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  void Task::setName ( QString name )
  {
    _M_name = name;
  }
  // ---------------------------------------------------------------------------------
  bool Task::isSoloEffort() const
  {
    return _M_solo_effort;
  }
  // ---------------------------------------------------------------------------------
  void Task::setIsSoloEffort ( bool s )
  {
    _M_solo_effort = s;
  }
  // ---------------------------------------------------------------------------------
  bool Task::isChargeable() const
  {
    return _M_chargeable;
  }
  // ---------------------------------------------------------------------------------
  void Task::setIsChargeable ( bool c )
  {
    _M_chargeable = c;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Task::creationDate() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
  void Task::setCreationDate ( QDateTime date )
  {
    _M_creation_date = date;
  }
  // ---------------------------------------------------------------------------------
  bool operator == (dp::Task const& lhs, dp::Task const& rhs)
  {
    if(lhs.id().isNull())
    {
      return (rhs.id().isNull());
    }
    return lhs.id() == rhs.id();
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
