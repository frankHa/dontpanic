#ifndef DP_LEAVE_TYPE_HPP
#define DP_LEAVE_TYPE_HPP
// ---------------------------------------------------------------------------------
#include "defines.hpp"
//Qt includes
#include <QString>
#include <QUuid>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  class LeaveType
  {
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      TYPE ( LeaveType );
      // ---------------------------------------------------------------------------------
      public:
      // ---------------------------------------------------------------------------------
      QUuid const& id() const;
      // ---------------------------------------------------------------------------------
      QString const& name() const;
      // ---------------------------------------------------------------------------------
      bool is_paid() const;
      // ---------------------------------------------------------------------------------
      QString const& description() const;
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      QUuid _M_id;
      // ---------------------------------------------------------------------------------
      QString _M_name;
      // ---------------------------------------------------------------------------------
      bool _M_paid;
      // ---------------------------------------------------------------------------------
      QString _M_description;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}//dp
// ---------------------------------------------------------------------------------
#endif //DP_LEAVE_TYPE_HPP