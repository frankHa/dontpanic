#include "libdontpanic/task.hpp"

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Task::Task()
      : _M_id ( QUuid::createUuid() )
      , _M_name ( "" )
      , _M_visible ( true )
      , _M_solo_effort ( true )
      , _M_chargeable ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  Task::Task ( QUuid const& id )
      : _M_id ( id )
      , _M_name ( "" )
      , _M_visible ( true )
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
  void Task::set_name ( QString name )
  {
    _M_name = name;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_visible() const
  {
    return _M_visible;
  }
  // ---------------------------------------------------------------------------------
  void Task::set_is_visible ( bool v )
  {
    _M_visible = v;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_solo_effort() const
  {
    return _M_solo_effort;
  }
  // ---------------------------------------------------------------------------------
  void Task::set_is_solo_effort ( bool s )
  {
    _M_solo_effort = s;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_chargeable() const
  {
    return _M_chargeable;
  }
  // ---------------------------------------------------------------------------------
  void Task::set_is_chargeable ( bool c )
  {
    _M_chargeable = c;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Task::creation_date() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
  void Task::set_creation_date ( QDateTime date )
  {
    _M_creation_date = date;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
