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
  Task& Task::setName ( QString name )
  {
    _M_name = name;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool Task::isSoloEffort() const
  {
    return _M_solo_effort;
  }
  // ---------------------------------------------------------------------------------
  Task& Task::setIsSoloEffort ( bool s )
  {
    _M_solo_effort = s;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  bool Task::isChargeable() const
  {
    return _M_chargeable;
  }
  // ---------------------------------------------------------------------------------
  Task& Task::setIsChargeable ( bool c )
  {
    _M_chargeable = c;
    return *this;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Task::creationDate() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
  Task& Task::setCreationDate ( QDateTime date )
  {
    _M_creation_date = date;
    return *this;
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
