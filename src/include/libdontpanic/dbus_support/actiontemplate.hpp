#ifndef DP_DBUS_ACTION_TEMPLATE_HPP
#define DP_DBUS_ACTION_TEMPLATE_HPP
//dp includes
#include "libdontpanic/defines.hpp"
#include "libdontpanic/actiontemplate.hpp"
//Qt includes
#include <QDBusArgument>
// ---------------------------------------------------------------------------------
Q_DECLARE_METATYPE ( dp::ActionTemplate )
Q_DECLARE_METATYPE ( dp::TemplateList )
namespace dp
{
  // ---------------------------------------------------------------------------------
  QDBusArgument const& operator >> ( QDBusArgument const&arg, dp::ActionTemplate & at );
  // ---------------------------------------------------------------------------------
  QDBusArgument & operator << ( QDBusArgument &arg, dp::ActionTemplate const& at );
  // ---------------------------------------------------------------------------------
}
#endif //DP_DBUS_ACTION_TEMPLATE_HPP
