#include "Task.hpp"

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  Task::Task()
      : _M_id ( 0 )
      , _M_name ( "" )
      , _M_visible ( true )
      , _M_solo_effort ( true )
      , _M_chargeable ( true )
      , _M_creation_date ( QDateTime::currentDateTime() ) {}
  // ---------------------------------------------------------------------------------
  uint64_t Task::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString const& Task::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_visible() const
  {
    return _M_visible;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_solo_effort() const
  {
    return _M_solo_effort;
  }
  // ---------------------------------------------------------------------------------
  bool Task::is_chargeable() const
  {
    return _M_chargeable;
  }
  // ---------------------------------------------------------------------------------
  QDateTime const& Task::creation_date() const
  {
    return _M_creation_date;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------