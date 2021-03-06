#include "libdontpanic/leavetype.hpp"
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  QUuid const& LeaveType::id() const
  {
    return _M_id;
  }
  // ---------------------------------------------------------------------------------
  QString const& LeaveType::name() const
  {
    return _M_name;
  }
  // ---------------------------------------------------------------------------------
  bool LeaveType::is_paid() const
  {
    return _M_paid;
  }
  // ---------------------------------------------------------------------------------
  QString const& LeaveType::description() const
  {
    return _M_description;
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
