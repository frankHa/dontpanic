#include "task.hpp"

// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  ///ctor
  task::task()
      : _M_id ( 0 )
      , _M_name ( "" )
      , _M_description ( "" ) {}
  // ---------------------------------------------------------------------------------
  long task::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString const& task::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  QString const& task::description() const
  {
    return _M_description;
  }
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
